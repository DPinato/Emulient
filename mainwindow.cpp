#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    uint64_t test = Utilities::stringToInt("0E:DC:BA:98:76:54");
    qDebug() << QString::number(test, 16) << "\t" << test;

    std::string testS = Utilities::intToMacAddress(test);
    qDebug() << testS.c_str();

    uint8_t *testU = new uint8_t [6];
    Utilities::intToMacAddress(test, testU);
    qDebug() << testU[0] << "\t" << testU[1] << "\t" << testU[2] << "\t"
                << testU[3] << "\t" << testU[4] << "\t" << testU[5] << "\t";

    delete testU;

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

    // for some reason, unless the functions below run qDebug(), it does not work
/*    if (Utilities::checkMacAddress(tmpSrc)) {
        qDebug() << "Good src MAC address";
    }
    if (Utilities::checkMacAddress(tmpDst)) {
        qDebug() << "Good dst MAC address";
    }
*/

    uint8_t *srcMacA = new uint8_t [6];
    uint8_t *dstMacA = new uint8_t [6];

    Utilities::intToMacAddress(Utilities::stringToInt(tmpSrc), srcMacA);
    Utilities::intToMacAddress(Utilities::stringToInt(tmpDst), dstMacA);


    qDebug() << srcMacA[0] << " " << srcMacA[1] << " " << srcMacA[2] << " "
             << srcMacA[3] << " " << srcMacA[4] << " " << srcMacA[5] << " ";
    qDebug() << dstMacA[0] << " " << dstMacA[1] << " " << dstMacA[2] << " "
             << dstMacA[3] << " " << dstMacA[4] << " " << dstMacA[5] << " ";


    int sockfd;
    struct ifreq if_idx;
    struct ifreq if_mac;
    int tx_len = 0;
    char sendbuf[BUF_SIZ];
    struct ether_header *eh = (struct ether_header *) sendbuf;
    struct iphdr *iph = (struct iphdr *) (sendbuf + sizeof(struct ether_header));
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
    eh->ether_shost[0] = srcMacA[0];
    eh->ether_shost[1] = srcMacA[1];
    eh->ether_shost[2] = srcMacA[2];
    eh->ether_shost[3] = srcMacA[3];
    eh->ether_shost[4] = srcMacA[4];
    eh->ether_shost[5] = srcMacA[5];

    // destination MAC address
    eh->ether_dhost[0] = dstMacA[0];
    eh->ether_dhost[1] = dstMacA[1];
    eh->ether_dhost[2] = dstMacA[2];
    eh->ether_dhost[3] = dstMacA[3];
    eh->ether_dhost[4] = dstMacA[4];
    eh->ether_dhost[5] = dstMacA[5];


    /* Ethertype field */
    eh->ether_type = htons(ETH_P_IP);

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
    socket_address.sll_addr[0] = dstMacA[0];
    socket_address.sll_addr[1] = dstMacA[1];
    socket_address.sll_addr[2] = dstMacA[2];
    socket_address.sll_addr[3] = dstMacA[3];
    socket_address.sll_addr[4] = dstMacA[4];
    socket_address.sll_addr[5] = dstMacA[5];


    /* Send packet */
    for (int i = 0; i < 1000; i++) {

        if (sendto(sockfd, sendbuf, tx_len, 0, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0)
            printf("Send failed\n");
    }


    qDebug() << "SENT FRAMES";


    delete srcMacA;
    delete dstMacA;

}
