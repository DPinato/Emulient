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
#include "linuxsocket.h"

class L2Helper;
class L3Helper;
class LinuxSocket;


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
	void updateIPv4Checksum();

	void on_l2PayloadCheckBox_clicked(bool checked);
	void on_autoComputeCheckBox_clicked(bool checked);
	void on_verEdit_editingFinished();
	void on_ihlEdit_editingFinished();
	void on_dscpEdit_editingFinished();
	void on_ecnEdit_editingFinished();
	void on_totLengthEdit_editingFinished();
	void on_identificationEdit_editingFinished();
	void on_flagsEdit_editingFinished();
	void on_fragOffsetEdit_editingFinished();
	void on_ttlEdit_editingFinished();
	void on_protocolEdit_editingFinished();
	void on_checksumEdit_editingFinished();
	void on_srcIPEdit_editingFinished();
	void on_dstIPEdit_editingFinished();

	void on_dot1qCheckBox_clicked(bool checked);

	void on_l3PayloadCheckBox_clicked(bool checked);

private:
	Ui::MainWindow *ui;

	// these are used for the main tab widget "Raw Frame"
	L2Helper *testL2;
	L3Helper *testL3;

	int length;		// size of Layer 2 payload

};

#endif // MAINWINDOW_H
