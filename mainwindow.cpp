#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	QMainWindow::setWindowTitle("Emulient");


	// initialise UI

	on_l2PayloadCheckBox_clicked(false);

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

*/



}

MainWindow::~MainWindow() {
	delete ui;
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
	std::string l2payload = ui->l2payloadEdit->toPlainText().toStdString();

	int length = 0;
	if (ui->l2PayloadCheckBox->isChecked()) {
		length = ceil((int)l2payload.length()/2.0);
	} else {
		length = 20;
	}
	uint8_t *l2PayloadHex = new uint8_t [length];
	int index = 0;



	// get src and dst MAC addresses
	Utilities::intToMacAddress(Utilities::stringToInt(tmpSrc), srcMacA);
	Utilities::intToMacAddress(Utilities::stringToInt(tmpDst), dstMacA);

	qDebug() << srcMacA[0] << " " << srcMacA[1] << " " << srcMacA[2] << " "
			 << srcMacA[3] << " " << srcMacA[4] << " " << srcMacA[5] << " ";
	qDebug() << dstMacA[0] << " " << dstMacA[1] << " " << dstMacA[2] << " "
			 << dstMacA[3] << " " << dstMacA[4] << " " << dstMacA[5] << " ";
	qDebug() << etherType;



	L3Helper *testL3 = new L3Helper(length, length);	// options not supported yet

	// set L2 header fields
	length = testL3->getIHL()*4;
	L2Helper *testL2 = new L2Helper(sizeof(struct ether_header)+length);	// will have to change when we put in 802.1Q tags
	testL2->setSrcMac(srcMacA);
	testL2->setDstMac(dstMacA);
	testL2->setEtherType(etherType);  // function in L2Helper does htons()


	if (ui->l2PayloadCheckBox->isChecked()) {
		// use what is inside the L2 custom frame box
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
		qDebug () << "l2PayloadHex length: " << length;

	} else {
		// use the parameters in the boxes
		// L3 STUFF
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
		testL3->setChecksum(
					(uint16_t)ui->checksumEdit->text().toUInt(NULL, 16));
		testL3->setSrcIP(L3Helper::ip4To32bitUint(ui->srcIPEdit->text().toStdString()));
		testL3->setDstIP(L3Helper::ip4To32bitUint(ui->dstIPEdit->text().toStdString()));

		testL2->setPayload((uint8_t *)testL3->getRawHeader(), length);

	}



	// TODO: EVERYTHING BELOW HERE SHOULD BE IN A DIFFERENT CLASS, OR AT LEAST SOMEWHERE ELSE
	int sockfd;
	struct ifreq if_idx;
	struct ifreq if_mac;

//    struct iphdr *iph = (struct iphdr *) (sendbuf + sizeof(struct ether_header));
	struct sockaddr_ll socket_address;
	char ifName[IFNAMSIZ];

	/* Get interface name */
/*    if (argc > 1)
		strcpy(ifName, argv[1]);
	else*/
	strcpy(ifName, DEFAULT_IF);

	/* Open RAW socket to send on */
	if ((sockfd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW)) == -1) {
		perror("socket");
	}

	/* Get the index of the interface to send on */
	memset(&if_idx, 0, sizeof(struct ifreq));
	strncpy(if_idx.ifr_name, ifName, IFNAMSIZ-1);
	if (ioctl(sockfd, SIOCGIFINDEX, &if_idx) < 0) { perror("SIOCGIFINDEX"); }

	/* Get the MAC address of the interface to send on */
	memset(&if_mac, 0, sizeof(struct ifreq));
	strncpy(if_mac.ifr_name, ifName, IFNAMSIZ-1);
	if (ioctl(sockfd, SIOCGIFHWADDR, &if_mac) < 0) { perror("SIOCGIFHWADDR"); }

	socket_address.sll_ifindex = if_idx.ifr_ifindex;	// index of network device

	socket_address.sll_halen = ETH_ALEN;	// address length

	/* Destination MAC */
	// this is the one that actually matters, it shows up in the frame header
	socket_address.sll_addr[0] = testL2->getDstMac()[0];
	socket_address.sll_addr[1] = testL2->getDstMac()[1];
	socket_address.sll_addr[2] = testL2->getDstMac()[2];
	socket_address.sll_addr[3] = testL2->getDstMac()[3];
	socket_address.sll_addr[4] = testL2->getDstMac()[4];
	socket_address.sll_addr[5] = testL2->getDstMac()[5];


	/* Send packet */
	int tx_len = sizeof(struct ether_header) + testL2->getPayloadSize();   // transmission length
	int bytesSent = sendto(sockfd, testL2->getSendbuf(), tx_len, 0
						   , (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll));
//    if (sendto(sockfd, sendbuf, tx_len, 0, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0)
	if (bytesSent < 0) { printf("Send failed\n"); }

	qDebug() << "SENT FRAME, bytesSent: " << bytesSent;


	delete srcMacA;
	delete dstMacA;
//    delete testL2;    // check what is happening with pointers here

}


void MainWindow::macAddressTableTest() {
	// generate frames with increasing source MAC addresses

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


	qDebug() << "SENT FRAMES";


	delete srcMac;

}

void MainWindow::on_runMacTableButton_clicked() {
	macAddressTableTest();

}

void MainWindow::on_l2PayloadCheckBox_clicked(bool checked) {
	// if checked, only show custom L2 payload box, hide all the fields above it
	ui->l2payloadEdit->setEnabled(checked);

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
	ui->checksumEdit->setEnabled(!checked);
	ui->srcIPEdit->setEnabled(!checked);
	ui->dstIPEdit->setEnabled(!checked);
	ui->optionsEdit->setEnabled(false);
}
