#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>

#include <string>
#include <new>
#include <iostream>
#include <bitset>
#include <sstream>

#include <QMainWindow>
#include <QDebug>
#include <QString>

#include "utilities.h"


#define DEFAULT_IF	"eth0"
#define BUF_SIZ	1024


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_sendButton_clicked();

    void sendFrame();

    void macAddressTableTest();

    void on_runMacTableButton_clicked();

private:
    Ui::MainWindow *ui;



//    uint8_t srcMac[6];  // TODO: handling this as a 48-bit int might be better
//    uint8_t dstMac[6];  // TODO: handling this as a 48-bit int might be better

    uint64_t srcMac;
    uint64_t dstMac;

};

#endif // MAINWINDOW_H
