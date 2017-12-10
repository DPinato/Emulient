#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->statusBar->setSizeGripEnabled(false);	// this does not seem to be working on Ubuntu
	QMainWindow::setWindowTitle("Emulient");


	// there is going to be some debug stuff here, since this function runs immediately when the program starts
/*
	uint64_t test = Utilities::stringToInt("0E:DC:BA:98:76:54");
	qDebug() << QString::number(test, 16) << "\t" << test;

	std::string testS = Utilities::intToMacAddress(test);
	qDebug() << testS.c_str();

	uint8_t *testU = new uint8_t [6];
	Utilities::intToMacAddress(test, testU);
	qDebug() << testU[0] << "\t" << testU[1] << "\t" << testU[2] << "\t"
				<< testU[3] << "\t" << testU[4] << "\t" << testU[5] << "\t";

	delete testU;



	std::string debugIP = Utilities::intToIPAddressStr(182982658);	// 10.232.24.2
	qDebug() << QString(debugIP.c_str());
	qDebug() << Utilities::ipAddressStrToInt(debugIP);


	uint32_t debugIPInt = Utilities::ipAddressStrToInt("255.255.255.255");
	qDebug() << debugIPInt;
	qDebug() << QString(Utilities::intToIPAddressStr(debugIPInt).c_str());

*/



	// TECHNICALLY the minimum size of a frame is the L2 header
	// the standard dictates however that the minimum frame size needs to be 64 Bytes
	testL2 = new L2Helper();

	if (ui->l2PayloadCheckBox->isChecked()) {
		std::string l2payload = ui->l2payloadEdit->toPlainText().toStdString();
		length = ceil((int)l2payload.length()/2.0);
	} else {
		length = 20;	// options not supported yet
	}

	testL3 = new L3Helper(length);	// options not supported yet


	history.resize(10);	// max history size 10
	historySize = 0;
	framesSent = 0;

	QString tmp = QApplication::arguments().at(0);
	defHistorySaveFile = tmp.left(tmp.lastIndexOf("/")+1).append("test.txt");
	qDebug() << defHistorySaveFile;




	// initialise GUI
	ui->autoComputeCheckBox->setChecked(true);
	ui->checksumEdit->setEnabled(false);
	on_dot1qCheckBox_clicked(false);
	on_l2PayloadCheckBox_clicked(false);

	ui->l3PayloadCheckBox->setChecked(false);
	on_l3PayloadCheckBox_clicked(false);

	ui->loadButton->setEnabled(false);	// history should be empty at this point

	getNetInterfaces();


}

MainWindow::~MainWindow() {
	delete ui;

	// delete the history
//	for (int i = 0; i < historySize; i++) {
//		delete history[i].l3p;
//		delete history[i].l2p;

//	}

	freeifaddrs(ifaddr);

}

void MainWindow::on_sendButton_clicked() {
	sendFrame();
}

void MainWindow::sendFrame() {
	// send frame using the src and dst MAC address from GUI
	std::string tmpSrc = ui->srcMacEdit->text().toStdString();
	std::string tmpDst = ui->dstMacEdit->text().toStdString();
	uint16_t etherType = ui->etherTypeEdit->text().toUInt(NULL, 16);
	uint8_t *srcMacA = new uint8_t [6];
	uint8_t *dstMacA = new uint8_t [6];



	// get src and dst MAC addresses
	Utilities::intToMacAddress(Utilities::stringToInt(tmpSrc), srcMacA);
	Utilities::intToMacAddress(Utilities::stringToInt(tmpDst), dstMacA);

//	qDebug() << srcMacA[0] << " " << srcMacA[1] << " " << srcMacA[2] << " "
//			 << srcMacA[3] << " " << srcMacA[4] << " " << srcMacA[5] << " ";
//	qDebug() << dstMacA[0] << " " << dstMacA[1] << " " << dstMacA[2] << " "
//			 << dstMacA[3] << " " << dstMacA[4] << " " << dstMacA[5] << " ";
//	qDebug() << etherType;



	// set L2 header fields
	testL2->init();
	testL2->setSrcMac(srcMacA);
	testL2->setDstMac(dstMacA);
	testL2->setEtherType(etherType);  // function in L2Helper does htons()

	if (ui->dot1qCheckBox->isChecked()) {
		testL2->setDot1qHeader((uint16_t)ui->tpidEdit->text().toUInt(NULL, 16),
							   (uint8_t)ui->pcpEdit->text().toUInt(NULL, 16),
							   (uint8_t)ui->deiEdit->text().toUInt(NULL, 16),
							   (uint16_t)ui->vlanTagEdit->text().toUInt(NULL, 16));
	}



	if (ui->l2PayloadCheckBox->isChecked()) {
		// use what is inside the L2 custom frame box
		std::string l2payload = ui->l2payloadEdit->toPlainText().toStdString();
		length = ceil((int)l2payload.length()/2.0);
		uint8_t *l2PayloadHex = new uint8_t [length*sizeof(uint8_t)];
		int index = 0;

		for (int i = 0; i < (int)l2payload.length()-1; i+=2) {
			// TODO: need to do error checking here
			// the contents of l2payloadEdit are in HEX, meaning that 2 characters make 1 Byte
			l2PayloadHex[index] = (uint8_t)strtoul(l2payload.substr(i, 2).c_str(), NULL, 16);
			qDebug() << "index: " << index << "\tl2PayloadHex str: " << l2payload.substr(i, 2).c_str();
			qDebug() << "l2PayloadHex: " << l2PayloadHex[index];
			index++;
		}

		if ((int)l2payload.length() % 2 == 1) {
			uint16_t tmp = (uint16_t)strtoul(l2payload.substr(l2payload.length()-1, 1).c_str(), NULL, 16);
			l2PayloadHex[index] = tmp<<4;
			qDebug() << "index: " << index << "\tl2PayloadHex str: " << tmp;
			qDebug() << "l2PayloadHex: " << l2PayloadHex[index];
		}

		testL2->setPayload(l2PayloadHex, length);
		qDebug () << "l2PayloadHex length: " << testL2->getPayloadSize();
		delete[] l2PayloadHex;

	} else {
		// use the parameters in the boxes
		if (ui->l3PayloadCheckBox->isChecked()) {
			// do this first, because setL3Payload() will reset the buffer
			// take L3 payload from textedit, if this is not checked packet will be empty
			std::string l3payload = ui->l3payloadEdit->toPlainText().toStdString();
			int l3_length = ceil((int)l3payload.length()/2.0);
			uint8_t *l3PayloadHex = new uint8_t [l3_length*sizeof(uint8_t)];
			int index3 = 0;

			qDebug() << "l3payload: " << QString(l3payload.c_str());

			// use what is inside the L3 custom frame box
			for (int i = 0; i < (int)l3payload.length()-1; i+=2) {
				// TODO: need to do error checking here
				// the contents of l2payloadEdit are in HEX, meaning that 2 characters make 1 Byte
				l3PayloadHex[index3] = (uint8_t)strtoul(l3payload.substr(i, 2).c_str(), NULL, 16);
				qDebug() << "index3: " << index3 << "\tl3payload str: " << l3payload.substr(i, 2).c_str();
				qDebug() << "l3PayloadHex: " << l3PayloadHex[index3];
				index3++;
			}

			if ((int)l3payload.length() % 2 == 1) {
				uint16_t tmp = (uint16_t)strtoul(l3payload.substr(l3payload.length()-1, 1).c_str(), NULL, 16);
				l3PayloadHex[index3] = tmp<<4;
				qDebug() << "index: " << index3 << "\tl3PayloadHex str: " << tmp;
				qDebug() << "l3PayloadHex: " << l3PayloadHex[index3];
			}


			testL3->setL3Payload(l3PayloadHex, l3_length);	// put L3 payload in the L3Helper
			delete[] l3PayloadHex;

			qDebug() << "l3PayloadHex length: " << testL3->getL3PayloadSize();
//			qDebug() << "checksum: " << testL3->computeIPv4Checksum();
//			qDebug() << "verify checksum: " << testL3->verifyIPv4Checksum();

		}


		// L3 STUFF
//		testL3->init();
		testL3->setVersion((uint8_t)ui->verEdit->text().toUInt(NULL, 16));
		testL3->setIHL((uint8_t)ui->ihlEdit->text().toUInt(NULL, 16));
		testL3->setDSCP((uint8_t)ui->dscpEdit->text().toUInt(NULL, 16));
		testL3->setECN((uint8_t)ui->ecnEdit->text().toUInt(NULL, 16));
		testL3->setTotLength((uint16_t)ui->totLengthEdit->text().toUInt(NULL, 16));
		testL3->setIdentification((uint16_t)ui->identificationEdit->text().toUInt(NULL, 16));
		testL3->setFlags((uint16_t)ui->flagsEdit->text().toUInt(NULL, 16));
		testL3->setFragOffset((uint16_t)ui->fragOffsetEdit->text().toUInt(NULL, 16));
		testL3->setTTL((uint8_t)ui->ttlEdit->text().toUInt(NULL, 16));
		testL3->setProtocol((uint8_t)ui->protocolEdit->text().toUInt(NULL, 16));
		testL3->setChecksum((uint16_t)ui->checksumEdit->text().toUInt(NULL, 16));
		testL3->setSrcIP(L3Helper::ip4To32bitUint(ui->srcIPEdit->text().toStdString()));
		testL3->setDstIP(L3Helper::ip4To32bitUint(ui->dstIPEdit->text().toStdString()));



		updateIPv4Checksum();	// update GUI with checksum
		int l2PayloadSize = testL3->getPacketSize();

		testL2->setPayload(testL3->getSendbuf(), l2PayloadSize);
		qDebug() << "l2PayloadSize: " << l2PayloadSize
				 << "\tL3PSize: " << testL3->getL3PayloadSize() << "\tihl: " << testL3->getIHL();
		qDebug() << "testL2->getPayloadSize(): " << testL2->getPayloadSize();


	}


	qDebug() << "frame size: " << testL2->getFrameSize();

	// DEBUG ============================================================================
//    testL3->showSendBuf(testL3->getL3PayloadSize() + testL3->getIHL()*4);	// show L3 buffer

/*	for (int i = 0; i < testL2->getFrameSize(); i+=4) {
		qDebug() << QString::number(testL2->getSendbuf()[i], 16) << "\t"
				 << QString::number(testL2->getSendbuf()[i+1], 16) << "\t"
				 << QString::number(testL2->getSendbuf()[i+2], 16) << "\t"
				 << QString::number(testL2->getSendbuf()[i+3], 16);
	}
*/
	//============================================================================


	int txLen = testL2->getFrameSize();   // transmission length

	// send frame
	std::string iface = ui->ifacesComboBox->itemText(ui->ifacesComboBox->currentIndex()).toStdString();
	LinuxSocket *testSock = new LinuxSocket(dstMacA, iface);
	testSock->send(txLen, testL2->getSendbuf());

	qDebug() << "\n";


	updateHistory(ui->saveEdit->text(), testL3, testL2,
				  ui->l3PayloadCheckBox->isChecked(), ui->l2PayloadCheckBox->isChecked());

	// update counters
	framesSent++;

	// update GUI
	ui->framesSentLabel->setText(QString::number(framesSent));
	ui->saveEdit->setText("");


	delete[] srcMacA;
	delete[] dstMacA;
	delete testSock;

}


void MainWindow::macAddressTableTest() {
	// generate frames with increasing source MAC addresses
	// TODO: update this function, it was build before the L2Helper/L3Helper and LinuxSocket classes were made

	int frameTotal = ui->frameNoEdit->text().toInt();
	uint64_t startMac = (uint64_t)Utilities::stringToInt(ui->macTableTestEdit->text().toStdString());
	uint8_t *srcMac = new uint8_t [6];


	uint64_t dstMac[6] = {0x22, 0x22, 0x22, 0x22, 0x22, 0x22};
	uint64_t bcastMac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	if (ui->bcastCheckBox->isChecked()) {
		std::copy(bcastMac, bcastMac+6, dstMac);
	}


	int sockfd;
	struct ifreq if_idx;
	struct ifreq if_mac;
	int tx_len = 0;
	char sendbuf[BUF_SIZ];

	struct ether_header *eh = (struct ether_header *) sendbuf;
	struct iphdr *iph = (struct iphdr *) (sendbuf + sizeof(struct ether_header));
	struct sockaddr_ll socket_address;
	char ifName[IFNAMSIZ];

	strcpy(ifName, DEFAULT_IF);

	if ((sockfd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW)) == -1) {
		perror("socket");
	}

	/* Get the index of the interface to send on */
	memset(&if_idx, 0, sizeof(struct ifreq));
	strncpy(if_idx.ifr_name, ifName, IFNAMSIZ-1);
	if (ioctl(sockfd, SIOCGIFINDEX, &if_idx) < 0)
		perror("SIOCGIFINDEX");

	/* Get the MAC address of the interface to send on */
	memset(&if_mac, 0, sizeof(struct ifreq));
	strncpy(if_mac.ifr_name, ifName, IFNAMSIZ-1);
	if (ioctl(sockfd, SIOCGIFHWADDR, &if_mac) < 0)
		perror("SIOCGIFHWADDR");

	/* Construct the Ethernet header */
	memset(sendbuf, 0, BUF_SIZ);

	// source MAC address
	eh->ether_shost[0] = srcMac[0];
	eh->ether_shost[1] = srcMac[1];
	eh->ether_shost[2] = srcMac[2];
	eh->ether_shost[3] = srcMac[3];
	eh->ether_shost[4] = srcMac[4];
	eh->ether_shost[5] = srcMac[5];

	// destination MAC address
	eh->ether_dhost[0] = dstMac[0];
	eh->ether_dhost[1] = dstMac[1];
	eh->ether_dhost[2] = dstMac[2];
	eh->ether_dhost[3] = dstMac[3];
	eh->ether_dhost[4] = dstMac[4];
	eh->ether_dhost[5] = dstMac[5];


	/* Ethertype field */
	std::string eTypeStr = ui->etherTypeEdit->text().toStdString();
	uint16_t etherType = (uint16_t)strtoul(eTypeStr.c_str(), NULL, 16);
//    eh->ether_type = htons(ETH_P_IP);
	eh->ether_type = htons(etherType);

	tx_len += sizeof(struct ether_header);

	/* Packet data */
	sendbuf[tx_len++] = 0xde;
	sendbuf[tx_len++] = 0xad;
	sendbuf[tx_len++] = 0xbe;
	sendbuf[tx_len++] = 0xef;

	/* Index of the network device */
	socket_address.sll_ifindex = if_idx.ifr_ifindex;

	/* Address length*/
	socket_address.sll_halen = ETH_ALEN;

	/* Destination MAC */
	// this is the one that actually matters, it shows up in the frame header
	socket_address.sll_addr[0] = dstMac[0];
	socket_address.sll_addr[1] = dstMac[1];
	socket_address.sll_addr[2] = dstMac[2];
	socket_address.sll_addr[3] = dstMac[3];
	socket_address.sll_addr[4] = dstMac[4];
	socket_address.sll_addr[5] = dstMac[5];


	/* Send packet */
	for (int i = 0; i < frameTotal; i++) {
		qDebug() << Utilities::intToMacAddress(startMac).c_str();

		// put the source MAC address in the frame
		Utilities::intToMacAddress(startMac++, srcMac);
		eh->ether_shost[0] = srcMac[0];
		eh->ether_shost[1] = srcMac[1];
		eh->ether_shost[2] = srcMac[2];
		eh->ether_shost[3] = srcMac[3];
		eh->ether_shost[4] = srcMac[4];
		eh->ether_shost[5] = srcMac[5];

		if (sendto(sockfd, sendbuf, tx_len, 0, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0)
			printf("%i Send failed\n", i);
	}


	qDebug() << "SENT " << frameTotal << " FRAMES";
	delete[] srcMac;

}

void MainWindow::updateIPv4Checksum() {
	// if the IPv4 checksum checkbox is checked, also recompute checksum
	// if it is not, only verify the checksum in the lineEdit, highlight it if it is incorrect
	if (ui->autoComputeCheckBox->isChecked()) {
		testL3->setChecksum(testL3->computeIPv4Checksum());
		ui->checksumEdit->setText(QString::number(htons(testL3->getIPHeader()->check), 16));
	}

//	qDebug() << "updateIPv4Checksum()\t" << testL3->verifyIPv4Checksum();
	if (testL3->verifyIPv4Checksum() != 0) {
		// checksum incorrect, show in the GUI just in case
		ui->checksumEdit->setStyleSheet("QLineEdit#checksumEdit{color:red}");
	} else {
		ui->checksumEdit->setStyleSheet("QLineEdit#checksumEdit{color:black}");
	}

}

void MainWindow::updateHistory(QString s, L3Helper *l3, L2Helper *l2, bool l3Flag, bool l2Flag) {
	// update the history vector
	// add new entries until the vector is full, then overwrite the older elements
	int index = framesSent % history.size();

	history[index].title = s;
	history[index].l3p = new L3Helper(*l3);
	history[index].l2p = new L2Helper(*l2);
	history[index].hasL3Payload = l3Flag;
	history[index].hasL2Payload = l2Flag;

	if (historySize < history.size()) {	historySize++; }

	qDebug() << "index: " << index << "\tframesSent: " << framesSent << "\thistorySize: " << historySize;

	// update qcombobox with frame histry
	if (historySize == 10) {
		// do not add anymore entries
		if (history[index].title.isEmpty()) {
			ui->comboBox->setItemText(index, QString("<untitled>" + QString::number(framesSent)));
		} else {
			ui->comboBox->setItemText(index, history[index].title);
		}
	} else {
		if (history[index].title.isEmpty()) {
			ui->comboBox->insertItem(index, QString("<untitled>" + QString::number(framesSent)));
		} else {
			ui->comboBox->insertItem(index, history[index].title);
		}
	}


	if (historySize > 0) {
		ui->loadButton->setEnabled(true);
	} else {
		ui->loadButton->setEnabled(false);
	}

}

bool MainWindow::saveHistoryToFile(QString fileName) {
	// save frames in the history vector to file
	QFile file(fileName);

	if (file.open(QIODevice::ReadWrite)) {
		QTextStream out(&file);

		for (int i = 0; i < historySize; i++) {
			// save the title give to this frame and the full L2 and L3 send buf
			out << history.at(i).title;
			out << ":";

			// L2 payload
			out << history.at(i).l2p->getFrameSize();
			out << ":";

			for (int j = 0; j < history.at(i).l2p->getFrameSize(); j++) {
				uint8_t n = history.at(i).l2p->getSendbuf()[j];
				out << QString::number(n, 16).rightJustified(2, '0');
			}


			// L3 payload
			out << ":";
			out << history.at(i).l3p->getPacketSize();
			out << ":";

			for (int j = 0; j < history.at(i).l3p->getPacketSize(); j++) {
				uint8_t n = history.at(i).l3p->getSendbuf()[j];
				out << QString::number(n, 16).rightJustified(2, '0');
			}

			out << "\n";

		}

		file.close();

	} else {
		return false;
	}


	return true;	// everything went ok

}

bool MainWindow::loadHistoryFromFile(QString fileName) {

}

bool MainWindow::loadFrameFromHistory(int index) {
	// take a frame from the history vector and load it in the L2Helper/L3Helper objects
	// update the GUI too
	qDebug() << "loadFrameFromHistory() index " << index;

	// do some error checking
	if (index > historySize) { return false; }

	// it is probably easier to re-create these
	testL2 = new L2Helper(*history[index].l2p);
	testL3 = new L3Helper(*history[index].l3p);


	// show values in GUI
	updateFrameGUI(testL3, testL2, history[index].hasL3Payload, history[index].hasL2Payload);
	ui->saveEdit->setText(history.at(index).title);


	return true;    // everything went ok

}

void MainWindow::updateFrameGUI(L3Helper *l3, L2Helper *l2, bool l3Flag, bool l2Flag) {
	// show the contents of the L3Helper and L2Helper objects in the GUI
	// l2Flag and l3Flag show whether the frame was built with a l2 or l3 custom payload

	// L2 stuff
	ui->srcMacEdit->setText(
				QString::fromStdString(
					Utilities::arrayToMacAddressStr(l2->getSrcMac())));
	ui->dstMacEdit->setText(
				QString::fromStdString(
					Utilities::arrayToMacAddressStr(l2->getDstMac())));
	ui->etherTypeEdit->setText(QString::number(l2->getEtherType(), 16).rightJustified(4, '0'));


	if (l2->hasDot1Q()) {
		ui->tpidEdit->setText(QString::number(l2->getTpid(), 16).rightJustified(4, '0'));
		ui->pcpEdit->setText(QString::number(l2->getPcp(), 16));
		ui->deiEdit->setText(QString::number(l2->getDei(), 16));
		ui->vlanTagEdit->setText(QString::number(l2->getVlanID(), 16).rightJustified(4, '0'));
	}
	ui->dot1qCheckBox->setChecked(l2->hasDot1Q());
	on_dot1qCheckBox_clicked(l2->hasDot1Q());

	ui->l2PayloadCheckBox->setChecked(l2Flag);
	on_l2PayloadCheckBox_clicked(l2Flag);


	QString tmpL2 = "";       // show l2 payload
	for (int i = 0; i < l2->getPayloadSize(); i++) {
		tmpL2.append(QString::number(l2->getPayload()[i], 16).rightJustified((2, '0', true)));

	}

	ui->l2payloadEdit->setText(tmpL2);



	// L3 stuff
	ui->verEdit->setText(QString::number(l3->getVersion(), 16));
	ui->ihlEdit->setText(QString::number(l3->getIHL(), 16));
	ui->dscpEdit->setText(QString::number(l3->getDSCP(), 16).rightJustified(2, '0'));
	ui->ecnEdit->setText(QString::number(l3->getECN(), 16));
	ui->totLengthEdit->setText(QString::number(htons(l3->getIPHeader()->tot_len), 16).rightJustified(4, '0'));
	ui->identificationEdit->setText(QString::number(htons(l3->getIPHeader()->id), 16).rightJustified(4, '0'));
	ui->flagsEdit->setText(QString::number(l3->getFlags(), 16));
	ui->fragOffsetEdit->setText(QString::number(l3->getFragOffset(), 16).rightJustified(4, '0'));
	ui->ttlEdit->setText(QString::number(l3->getIPHeader()->ttl, 16));
	ui->protocolEdit->setText(QString::number(l3->getIPHeader()->protocol, 16));
	ui->checksumEdit->setText(QString::number(htons(l3->getIPHeader()->check), 16).rightJustified(4, '0'));

	ui->srcIPEdit->setText(QString(Utilities::intToIPAddressStr(l3->getIPHeader()->saddr).c_str()));
	ui->dstIPEdit->setText(QString(Utilities::intToIPAddressStr(l3->getIPHeader()->daddr).c_str()));

	ui->autoComputeCheckBox->setChecked(true);
	on_autoComputeCheckBox_clicked(true);

	ui->l3PayloadCheckBox->setChecked(l3Flag);
	on_l3PayloadCheckBox_clicked(l3Flag);

	QString tmpL3 = "";       // show l2 payload
	for (int i = 0; i < l3->getL3PayloadSize(); i++) {
		tmpL3.append(QString::number(l3->getL3Payload()[i], 16).rightJustified((2, '0', true)));

	}

	ui->l3payloadEdit->setText(tmpL3);

}

bool MainWindow::getNetInterfaces() {
	// get the network interfaces that are currently connected to the system
	// store them in an array to be able to retrieve them later
	// also show them in ifacesComboBox

	if (getifaddrs(&ifaddr) == -1) {
		perror("getifaddrs");
		return false;
	}


	for (ifa = ifaddr, nFam = 0; ifa != NULL; ifa = ifa->ifa_next, nFam++) {
		// cycle through all the interfaces, only show the ones of family AF_PACKET
		if (ifa->ifa_addr == NULL) { continue; }

		family = ifa->ifa_addr->sa_family;

		if (family == AF_PACKET) {
			// show interface in combo box
			ui->ifacesComboBox->addItem(QString(ifa->ifa_name));


		}

	}

	return true;	// everything went well

}

void MainWindow::on_runMacTableButton_clicked() {
	macAddressTableTest();
}

void MainWindow::on_l2PayloadCheckBox_clicked(bool checked) {
	// if checked, only show custom L2 payload box, hide all the fields above it
	ui->l2payloadEdit->setEnabled(checked);
	ui->l3PayloadCheckBox->setEnabled(!checked);
	ui->l3payloadEdit->setEnabled(ui->l3PayloadCheckBox->isChecked());

	ui->verEdit->setEnabled(!checked);
	ui->ihlEdit->setEnabled(!checked);
	ui->dscpEdit->setEnabled(!checked);
	ui->ecnEdit->setEnabled(!checked);
	ui->totLengthEdit->setEnabled(!checked);
	ui->identificationEdit->setEnabled(!checked);
	ui->flagsEdit->setEnabled(!checked);
	ui->fragOffsetEdit->setEnabled(!checked);
	ui->ttlEdit->setEnabled(!checked);
	ui->protocolEdit->setEnabled(!checked);
	ui->srcIPEdit->setEnabled(!checked);
	ui->dstIPEdit->setEnabled(!checked);

	ui->optionsEdit->setEnabled(false);

	// this should be enabled only if the proper checkbox is checked
	ui->checksumEdit->setEnabled(!ui->autoComputeCheckBox->isChecked());

}

void MainWindow::on_autoComputeCheckBox_clicked(bool checked) {
	// Layer 3 checksum needs to be autocomputed, put in the box and in the L3Helper object
	// whenever a L3 header field is changed, checksum needs to be recomputed
	ui->checksumEdit->setEnabled(!checked);
	updateIPv4Checksum();
}

void MainWindow::on_verEdit_editingFinished() {
	// make sure L3 header checksum if recomputed
	testL3->setVersion((uint8_t)ui->verEdit->text().toUInt(NULL, 16));
	updateIPv4Checksum();
}

void MainWindow::on_ihlEdit_editingFinished() {
	// make sure L3 header checksum if recomputed
	testL3->setIHL((uint8_t)ui->ihlEdit->text().toUInt(NULL, 16));
	updateIPv4Checksum();
}

void MainWindow::on_dscpEdit_editingFinished() {
	// make sure L3 header checksum if recomputed
	testL3->setDSCP((uint8_t)ui->dscpEdit->text().toUInt(NULL, 16));
	updateIPv4Checksum();
}

void MainWindow::on_ecnEdit_editingFinished() {
	// make sure L3 header checksum if recomputed
	testL3->setECN((uint8_t)ui->ecnEdit->text().toUInt(NULL, 16));
	updateIPv4Checksum();
}

void MainWindow::on_totLengthEdit_editingFinished() {
	// make sure L3 header checksum if recomputed
	testL3->setTotLength((uint16_t)ui->totLengthEdit->text().toUInt(NULL, 16));
	updateIPv4Checksum();
}

void MainWindow::on_identificationEdit_editingFinished() {
	// make sure L3 header checksum if recomputed
	testL3->setIdentification((uint16_t)ui->identificationEdit->text().toUInt(NULL, 16));
	updateIPv4Checksum();
}

void MainWindow::on_flagsEdit_editingFinished() {
	// make sure L3 header checksum if recomputed
	testL3->setFlags((uint16_t)ui->flagsEdit->text().toUInt(NULL, 16));
	updateIPv4Checksum();
}

void MainWindow::on_fragOffsetEdit_editingFinished() {
	// make sure L3 header checksum if recomputed
	testL3->setFragOffset((uint16_t)ui->fragOffsetEdit->text().toUInt(NULL, 16));
	updateIPv4Checksum();
}

void MainWindow::on_ttlEdit_editingFinished() {
	// make sure L3 header checksum if recomputed
	testL3->setFragOffset((uint16_t)ui->ttlEdit->text().toUInt(NULL, 16));
	updateIPv4Checksum();
}

void MainWindow::on_protocolEdit_editingFinished() {
	// make sure L3 header checksum if recomputed
	testL3->setProtocol((uint8_t)ui->protocolEdit->text().toUInt(NULL, 16));
	updateIPv4Checksum();
}

void MainWindow::on_checksumEdit_editingFinished() {
	// check if the checksum is ok, otherwise
	testL3->setChecksum((uint16_t)ui->checksumEdit->text().toUInt(NULL, 16));
	updateIPv4Checksum();
}

void MainWindow::on_srcIPEdit_editingFinished() {
	// make sure L3 header checksum if recomputed
	testL3->setSrcIP(L3Helper::ip4To32bitUint(ui->srcIPEdit->text().toStdString()));
	updateIPv4Checksum();
}

void MainWindow::on_dstIPEdit_editingFinished() {
	// make sure L3 header checksum if recomputed
	testL3->setDstIP(L3Helper::ip4To32bitUint(ui->dstIPEdit->text().toStdString()));
	updateIPv4Checksum();
}

void MainWindow::on_dot1qCheckBox_clicked(bool checked) {
	// if checked, allow editing line edits for 802.1Q header
	ui->tpidEdit->setEnabled(checked);
	ui->pcpEdit->setEnabled(checked);
	ui->deiEdit->setEnabled(checked);
	ui->vlanTagEdit->setEnabled(checked);

}

void MainWindow::on_l3PayloadCheckBox_clicked(bool checked) {
	// if checked, allow editing the L3 payload text edit
	ui->l3payloadEdit->setEnabled(checked);
}

void MainWindow::on_loadButton_clicked() {
	loadFrameFromHistory(ui->comboBox->currentIndex());
}

void MainWindow::on_actionSave_History_triggered() {
	saveHistoryToFile(defHistorySaveFile);
}
