/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionQuit;
    QAction *actionSave_History;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QPushButton *sendButton;
    QLineEdit *srcMacEdit;
    QLabel *label;
    QLineEdit *dstMacEdit;
    QLabel *label_2;
    QLabel *label_6;
    QLineEdit *pcpEdit;
    QLineEdit *etherTypeEdit;
    QTextEdit *l2payloadEdit;
    QFrame *line;
    QLabel *label_8;
    QLineEdit *verEdit;
    QLabel *label_9;
    QLineEdit *ihlEdit;
    QLabel *label_10;
    QLineEdit *dscpEdit;
    QLabel *label_11;
    QLineEdit *ecnEdit;
    QLabel *label_12;
    QLineEdit *totLengthEdit;
    QLineEdit *identificationEdit;
    QLabel *label_13;
    QLineEdit *flagsEdit;
    QLabel *label_14;
    QLineEdit *fragOffsetEdit;
    QLabel *label_15;
    QLabel *label_16;
    QLineEdit *ttlEdit;
    QLabel *label_17;
    QLineEdit *protocolEdit;
    QLineEdit *checksumEdit;
    QLabel *label_18;
    QLabel *label_19;
    QLineEdit *srcIPEdit;
    QLabel *label_20;
    QLineEdit *dstIPEdit;
    QCheckBox *autoComputeCheckBox;
    QLabel *label_21;
    QLineEdit *optionsEdit;
    QCheckBox *l2PayloadCheckBox;
    QCheckBox *l3PayloadCheckBox;
    QTextEdit *l3payloadEdit;
    QCheckBox *dot1qCheckBox;
    QLabel *label_7;
    QLineEdit *tpidEdit;
    QLabel *label_22;
    QLabel *label_23;
    QLineEdit *deiEdit;
    QLabel *label_24;
    QLineEdit *vlanTagEdit;
    QLineEdit *saveEdit;
    QPushButton *loadButton;
    QComboBox *comboBox;
    QLabel *label_25;
    QLabel *label_26;
    QComboBox *ifacesComboBox;
    QLabel *framesSentLabel;
    QWidget *tab2;
    QLabel *label_3;
    QLineEdit *macTableTestEdit;
    QLabel *label_4;
    QLineEdit *frameNoEdit;
    QPushButton *runMacTableButton;
    QCheckBox *bcastCheckBox;
    QWidget *tab;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSave;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(700, 732);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionSave_History = new QAction(MainWindow);
        actionSave_History->setObjectName(QStringLiteral("actionSave_History"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 681, 671));
        tab1 = new QWidget();
        tab1->setObjectName(QStringLiteral("tab1"));
        sendButton = new QPushButton(tab1);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        sendButton->setGeometry(QRect(20, 600, 89, 31));
        srcMacEdit = new QLineEdit(tab1);
        srcMacEdit->setObjectName(QStringLiteral("srcMacEdit"));
        srcMacEdit->setGeometry(QRect(150, 20, 141, 25));
        srcMacEdit->setMaxLength(17);
        label = new QLabel(tab1);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 121, 25));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        dstMacEdit = new QLineEdit(tab1);
        dstMacEdit->setObjectName(QStringLiteral("dstMacEdit"));
        dstMacEdit->setGeometry(QRect(150, 50, 141, 25));
        dstMacEdit->setMaxLength(17);
        label_2 = new QLabel(tab1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 50, 121, 25));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(tab1);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 80, 121, 25));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pcpEdit = new QLineEdit(tab1);
        pcpEdit->setObjectName(QStringLiteral("pcpEdit"));
        pcpEdit->setEnabled(true);
        pcpEdit->setGeometry(QRect(420, 80, 21, 25));
        pcpEdit->setMaxLength(1);
        etherTypeEdit = new QLineEdit(tab1);
        etherTypeEdit->setObjectName(QStringLiteral("etherTypeEdit"));
        etherTypeEdit->setGeometry(QRect(150, 80, 41, 25));
        etherTypeEdit->setMaxLength(6);
        l2payloadEdit = new QTextEdit(tab1);
        l2payloadEdit->setObjectName(QStringLiteral("l2payloadEdit"));
        l2payloadEdit->setGeometry(QRect(20, 140, 641, 91));
        l2payloadEdit->setAcceptRichText(true);
        line = new QFrame(tab1);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(20, 240, 641, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_8 = new QLabel(tab1);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 270, 61, 25));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        verEdit = new QLineEdit(tab1);
        verEdit->setObjectName(QStringLiteral("verEdit"));
        verEdit->setGeometry(QRect(80, 270, 31, 25));
        verEdit->setMaxLength(1);
        label_9 = new QLabel(tab1);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(150, 270, 31, 25));
        label_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ihlEdit = new QLineEdit(tab1);
        ihlEdit->setObjectName(QStringLiteral("ihlEdit"));
        ihlEdit->setGeometry(QRect(180, 270, 31, 25));
        ihlEdit->setMaxLength(1);
        label_10 = new QLabel(tab1);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(250, 270, 51, 25));
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        dscpEdit = new QLineEdit(tab1);
        dscpEdit->setObjectName(QStringLiteral("dscpEdit"));
        dscpEdit->setGeometry(QRect(300, 270, 31, 25));
        dscpEdit->setMaxLength(2);
        label_11 = new QLabel(tab1);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(370, 270, 41, 25));
        label_11->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ecnEdit = new QLineEdit(tab1);
        ecnEdit->setObjectName(QStringLiteral("ecnEdit"));
        ecnEdit->setGeometry(QRect(410, 270, 31, 25));
        ecnEdit->setMaxLength(1);
        label_12 = new QLabel(tab1);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(480, 270, 101, 25));
        label_12->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        totLengthEdit = new QLineEdit(tab1);
        totLengthEdit->setObjectName(QStringLiteral("totLengthEdit"));
        totLengthEdit->setGeometry(QRect(580, 270, 51, 25));
        totLengthEdit->setMaxLength(4);
        identificationEdit = new QLineEdit(tab1);
        identificationEdit->setObjectName(QStringLiteral("identificationEdit"));
        identificationEdit->setGeometry(QRect(120, 300, 51, 25));
        identificationEdit->setMaxLength(4);
        label_13 = new QLabel(tab1);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(20, 300, 101, 25));
        label_13->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        flagsEdit = new QLineEdit(tab1);
        flagsEdit->setObjectName(QStringLiteral("flagsEdit"));
        flagsEdit->setGeometry(QRect(260, 300, 31, 25));
        flagsEdit->setMaxLength(1);
        label_14 = new QLabel(tab1);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(220, 300, 41, 25));
        label_14->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        fragOffsetEdit = new QLineEdit(tab1);
        fragOffsetEdit->setObjectName(QStringLiteral("fragOffsetEdit"));
        fragOffsetEdit->setGeometry(QRect(460, 300, 51, 25));
        fragOffsetEdit->setMaxLength(4);
        label_15 = new QLabel(tab1);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(340, 300, 121, 25));
        label_15->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_16 = new QLabel(tab1);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(20, 330, 41, 25));
        label_16->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ttlEdit = new QLineEdit(tab1);
        ttlEdit->setObjectName(QStringLiteral("ttlEdit"));
        ttlEdit->setGeometry(QRect(60, 330, 31, 25));
        ttlEdit->setMaxLength(2);
        label_17 = new QLabel(tab1);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(130, 330, 71, 25));
        label_17->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        protocolEdit = new QLineEdit(tab1);
        protocolEdit->setObjectName(QStringLiteral("protocolEdit"));
        protocolEdit->setGeometry(QRect(200, 330, 31, 25));
        protocolEdit->setMaxLength(2);
        checksumEdit = new QLineEdit(tab1);
        checksumEdit->setObjectName(QStringLiteral("checksumEdit"));
        checksumEdit->setGeometry(QRect(430, 330, 51, 25));
        checksumEdit->setMaxLength(4);
        label_18 = new QLabel(tab1);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(350, 330, 81, 25));
        label_18->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_19 = new QLabel(tab1);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(20, 360, 71, 25));
        label_19->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        srcIPEdit = new QLineEdit(tab1);
        srcIPEdit->setObjectName(QStringLiteral("srcIPEdit"));
        srcIPEdit->setGeometry(QRect(90, 360, 131, 25));
        srcIPEdit->setMaxLength(15);
        label_20 = new QLabel(tab1);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(240, 360, 111, 25));
        label_20->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        dstIPEdit = new QLineEdit(tab1);
        dstIPEdit->setObjectName(QStringLiteral("dstIPEdit"));
        dstIPEdit->setGeometry(QRect(350, 360, 131, 25));
        dstIPEdit->setMaxLength(15);
        autoComputeCheckBox = new QCheckBox(tab1);
        autoComputeCheckBox->setObjectName(QStringLiteral("autoComputeCheckBox"));
        autoComputeCheckBox->setGeometry(QRect(490, 330, 121, 23));
        label_21 = new QLabel(tab1);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(20, 390, 71, 25));
        label_21->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        optionsEdit = new QLineEdit(tab1);
        optionsEdit->setObjectName(QStringLiteral("optionsEdit"));
        optionsEdit->setEnabled(false);
        optionsEdit->setGeometry(QRect(90, 390, 571, 25));
        optionsEdit->setMaxLength(32);
        l2PayloadCheckBox = new QCheckBox(tab1);
        l2PayloadCheckBox->setObjectName(QStringLiteral("l2PayloadCheckBox"));
        l2PayloadCheckBox->setGeometry(QRect(20, 110, 141, 31));
        l2PayloadCheckBox->setChecked(false);
        l3PayloadCheckBox = new QCheckBox(tab1);
        l3PayloadCheckBox->setObjectName(QStringLiteral("l3PayloadCheckBox"));
        l3PayloadCheckBox->setGeometry(QRect(20, 420, 141, 31));
        l3PayloadCheckBox->setChecked(false);
        l3payloadEdit = new QTextEdit(tab1);
        l3payloadEdit->setObjectName(QStringLiteral("l3payloadEdit"));
        l3payloadEdit->setGeometry(QRect(20, 450, 641, 91));
        l3payloadEdit->setAcceptRichText(true);
        dot1qCheckBox = new QCheckBox(tab1);
        dot1qCheckBox->setObjectName(QStringLiteral("dot1qCheckBox"));
        dot1qCheckBox->setGeometry(QRect(340, 20, 92, 31));
        label_7 = new QLabel(tab1);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(370, 50, 51, 25));
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tpidEdit = new QLineEdit(tab1);
        tpidEdit->setObjectName(QStringLiteral("tpidEdit"));
        tpidEdit->setEnabled(true);
        tpidEdit->setGeometry(QRect(420, 50, 41, 25));
        tpidEdit->setMaxLength(4);
        label_22 = new QLabel(tab1);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(370, 80, 51, 25));
        label_22->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_23 = new QLabel(tab1);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(500, 50, 41, 25));
        label_23->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        deiEdit = new QLineEdit(tab1);
        deiEdit->setObjectName(QStringLiteral("deiEdit"));
        deiEdit->setEnabled(true);
        deiEdit->setGeometry(QRect(570, 50, 21, 25));
        deiEdit->setMaxLength(1);
        label_24 = new QLabel(tab1);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(500, 80, 71, 25));
        label_24->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        vlanTagEdit = new QLineEdit(tab1);
        vlanTagEdit->setObjectName(QStringLiteral("vlanTagEdit"));
        vlanTagEdit->setEnabled(true);
        vlanTagEdit->setGeometry(QRect(570, 80, 41, 25));
        vlanTagEdit->setMaxLength(3);
        saveEdit = new QLineEdit(tab1);
        saveEdit->setObjectName(QStringLiteral("saveEdit"));
        saveEdit->setGeometry(QRect(390, 560, 271, 31));
        saveEdit->setMaxLength(30);
        loadButton = new QPushButton(tab1);
        loadButton->setObjectName(QStringLiteral("loadButton"));
        loadButton->setGeometry(QRect(268, 600, 111, 31));
        comboBox = new QComboBox(tab1);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(390, 600, 271, 31));
        label_25 = new QLabel(tab1);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(330, 560, 51, 25));
        label_25->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_26 = new QLabel(tab1);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(20, 560, 71, 25));
        label_26->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ifacesComboBox = new QComboBox(tab1);
        ifacesComboBox->setObjectName(QStringLiteral("ifacesComboBox"));
        ifacesComboBox->setGeometry(QRect(100, 560, 131, 31));
        framesSentLabel = new QLabel(tab1);
        framesSentLabel->setObjectName(QStringLiteral("framesSentLabel"));
        framesSentLabel->setGeometry(QRect(120, 600, 81, 31));
        QFont font;
        font.setPointSize(14);
        framesSentLabel->setFont(font);
        framesSentLabel->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QStringLiteral("tab2"));
        label_3 = new QLabel(tab2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 20, 121, 21));
        macTableTestEdit = new QLineEdit(tab2);
        macTableTestEdit->setObjectName(QStringLiteral("macTableTestEdit"));
        macTableTestEdit->setGeometry(QRect(140, 20, 141, 25));
        macTableTestEdit->setMaxLength(17);
        label_4 = new QLabel(tab2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(290, 20, 81, 21));
        frameNoEdit = new QLineEdit(tab2);
        frameNoEdit->setObjectName(QStringLiteral("frameNoEdit"));
        frameNoEdit->setGeometry(QRect(370, 20, 71, 25));
        frameNoEdit->setMaxLength(7);
        runMacTableButton = new QPushButton(tab2);
        runMacTableButton->setObjectName(QStringLiteral("runMacTableButton"));
        runMacTableButton->setGeometry(QRect(580, 20, 89, 25));
        bcastCheckBox = new QCheckBox(tab2);
        bcastCheckBox->setObjectName(QStringLiteral("bcastCheckBox"));
        bcastCheckBox->setGeometry(QRect(460, 20, 92, 23));
        tabWidget->addTab(tab2, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 700, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuSave = new QMenu(menuFile);
        menuSave->setObjectName(QStringLiteral("menuSave"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(menuSave->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuSave->addAction(actionSave_History);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", Q_NULLPTR));
        actionSave_History->setText(QApplication::translate("MainWindow", "Save History", Q_NULLPTR));
        sendButton->setText(QApplication::translate("MainWindow", "SEND", Q_NULLPTR));
        srcMacEdit->setText(QApplication::translate("MainWindow", "08:00:27:48:69:25", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Src MAC address", Q_NULLPTR));
        dstMacEdit->setText(QApplication::translate("MainWindow", "01:80:C2:00:00:00", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Dst MAC address", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Ethertype", Q_NULLPTR));
        pcpEdit->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        etherTypeEdit->setText(QApplication::translate("MainWindow", "0800", Q_NULLPTR));
        l2payloadEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">4242030000000000000008002748692500000000000008002748692580040000140002000f00</p></body></html>", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Version", Q_NULLPTR));
        verEdit->setText(QApplication::translate("MainWindow", "4", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "IHL", Q_NULLPTR));
        ihlEdit->setText(QApplication::translate("MainWindow", "5", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "DSCP", Q_NULLPTR));
        dscpEdit->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "ECN", Q_NULLPTR));
        ecnEdit->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "Total Length", Q_NULLPTR));
        totLengthEdit->setText(QApplication::translate("MainWindow", "14", Q_NULLPTR));
        identificationEdit->setText(QApplication::translate("MainWindow", "4dc0", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "Identification", Q_NULLPTR));
        flagsEdit->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "Flags", Q_NULLPTR));
        fragOffsetEdit->setText(QApplication::translate("MainWindow", "123", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "Fragment Offset", Q_NULLPTR));
        label_16->setText(QApplication::translate("MainWindow", "TTL", Q_NULLPTR));
        ttlEdit->setText(QApplication::translate("MainWindow", "80", Q_NULLPTR));
        label_17->setText(QApplication::translate("MainWindow", "Protocol", Q_NULLPTR));
        protocolEdit->setText(QApplication::translate("MainWindow", "6", Q_NULLPTR));
        checksumEdit->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_18->setText(QApplication::translate("MainWindow", "Checksum", Q_NULLPTR));
        label_19->setText(QApplication::translate("MainWindow", "Source IP", Q_NULLPTR));
        srcIPEdit->setText(QApplication::translate("MainWindow", "192.168.128.24", Q_NULLPTR));
        label_20->setText(QApplication::translate("MainWindow", "Destination IP", Q_NULLPTR));
        dstIPEdit->setText(QApplication::translate("MainWindow", "8.8.8.8", Q_NULLPTR));
        autoComputeCheckBox->setText(QApplication::translate("MainWindow", "Auto-compute", Q_NULLPTR));
        label_21->setText(QApplication::translate("MainWindow", "Options", Q_NULLPTR));
        optionsEdit->setText(QApplication::translate("MainWindow", "NOT SUPPORTED YET", Q_NULLPTR));
        l2PayloadCheckBox->setText(QApplication::translate("MainWindow", "L2 payload (HEX)", Q_NULLPTR));
        l3PayloadCheckBox->setText(QApplication::translate("MainWindow", "L3 payload (HEX)", Q_NULLPTR));
        l3payloadEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">e591001548c7e4640000000070022000a4590000020405b401010402</p></body></html>", Q_NULLPTR));
        dot1qCheckBox->setText(QApplication::translate("MainWindow", "802.1Q", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "TPID", Q_NULLPTR));
        tpidEdit->setText(QApplication::translate("MainWindow", "8100", Q_NULLPTR));
        label_22->setText(QApplication::translate("MainWindow", "PCP", Q_NULLPTR));
        label_23->setText(QApplication::translate("MainWindow", "DEI", Q_NULLPTR));
        deiEdit->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_24->setText(QApplication::translate("MainWindow", "VLAN ID", Q_NULLPTR));
        vlanTagEdit->setText(QApplication::translate("MainWindow", "20", Q_NULLPTR));
        saveEdit->setText(QString());
        loadButton->setText(QApplication::translate("MainWindow", "LOAD FRAME", Q_NULLPTR));
        label_25->setText(QApplication::translate("MainWindow", "Name:", Q_NULLPTR));
        label_26->setText(QApplication::translate("MainWindow", "Interface:", Q_NULLPTR));
        framesSentLabel->setText(QApplication::translate("MainWindow", "<sent #>", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("MainWindow", "Raw Frame / IPv4", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "MAC Table, from", Q_NULLPTR));
        macTableTestEdit->setText(QApplication::translate("MainWindow", "12:34:bb:aa:cc:dd", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "no. frames:", Q_NULLPTR));
        frameNoEdit->setText(QApplication::translate("MainWindow", "100", Q_NULLPTR));
        runMacTableButton->setText(QApplication::translate("MainWindow", "RUN", Q_NULLPTR));
        bcastCheckBox->setText(QApplication::translate("MainWindow", "Broadcast", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QApplication::translate("MainWindow", "Stress Tests", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Presets", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuSave->setTitle(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
