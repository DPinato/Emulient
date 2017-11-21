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
#include <netinet/ip.h>

#include <string>
#include <new>
#include <iostream>
#include <bitset>
#include <sstream>

#include <QMainWindow>
#include <QDebug>
#include <QString>

#include "utilities.h"
#include "l2helper.h"
#include "l3helper.h"

class L2Helper;
class L3Helper;


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
	void on_runMacTableButton_clicked();

	void sendFrame();
	void macAddressTableTest();

	void on_l2PayloadCheckBox_clicked(bool checked);

private:
	Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
