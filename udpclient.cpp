#include <QGridLayout>
#include <QTimer>
#include <QDateTime>
#include <QHostAddress>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QProcess>
#include "udpclient.h"

UdpClient::UdpClient(QWidget *parent)
    : QDialog(parent)
{
    //bind this application on 8086 port, so OS will know the packet is for you
    mUdpSocket.bind(8086);// bind 8086 for Tacos, Tacos should send to this port.
    connect(&mUdpSocket,SIGNAL(readyRead()),SLOT(onProcessPendingDatagrams()));
    // new components
    mIpLabel = new QLabel(tr("Tacos IP(On Board):"));
    mPortLabel = new QLabel(tr("Tacos port(On Board):"));
    mOnOffLineLabel = new QLabel(tr("online status:"));
    mDoorLabel = new QLabel(tr("Door:"));
    mAlarmLabel = new QLabel(tr("Alarm:"));
    mIpLineEdit = new QLineEdit;
    mPortLineEdit = new QLineEdit;
    mOnOffLineLineEdit = new QLineEdit;
    mOnOffLineLineEdit->setReadOnly(true);
    mDoorQComboBox = new QComboBox;
    mAlarmLineEdit = new QLineEdit;
    mAlarmLineEdit->setReadOnly(true);
    mDoorQComboBox->addItem(tr("Open"));
    mDoorQComboBox->addItem(tr("Close"));
    connect(mDoorQComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(on_sel(const QString &)));

    //connect on_mConnectPushButton_clicked function to clicked signal
    mConnectPushButton = new QPushButton(tr("GO!!"));
    connect(mConnectPushButton, SIGNAL(clicked()), this, SLOT(on_mConnectPushButton_clicked()));
    //new a layout componet for adding items inside
    QGridLayout *mainLayout = new QGridLayout;
    //get local ip address{
    QString localHost = QHostInfo::localHostName();
    QString ipAddr;
    QHostInfo info = QHostInfo::fromName(localHost);
    info.addresses();//QHostInfo address函数获取本机ip地址
    //如果存在多条ip地址ipv4和ipv6：
    foreach(QHostAddress address,info.addresses())
    {
        if(address.protocol()==QAbstractSocket::IPv4Protocol){//只取ipv4协议的地址
            qDebug()<<address.toString();
            ipAddr = address.toString();
        }
    }
    mLocalIpAddress = new QLabel(ipAddr);
    mLocalUdpPort = new QLabel(tr("local port 8086"));
    //get local ip address}

    mTacosReportTextEdit = new QTextEdit;

    mainLayout->addWidget(mLocalIpAddress,0,0);
    mainLayout->addWidget(mLocalUdpPort,0,1);

    mainLayout->addWidget(mIpLabel,1,0);
    mainLayout->addWidget(mIpLineEdit,1,1);
    mainLayout->addWidget(mPortLabel,2,0);
    mainLayout->addWidget(mPortLineEdit,2,1);
    mainLayout->addWidget(mConnectPushButton,2,2);



    mainLayout->addWidget(mOnOffLineLabel,3,0);
    mainLayout->addWidget(mOnOffLineLineEdit,3,1);

    mainLayout->addWidget(mDoorLabel,4,0);
    mainLayout->addWidget(mDoorQComboBox,4,1);

    mainLayout->addWidget(mAlarmLabel,5,0);
    mainLayout->addWidget(mAlarmLineEdit,5,1);

    mainLayout->addWidget(mTacosReportTextEdit,6,0);


    setLayout(mainLayout);
    setWindowTitle(tr("Tacos Station"));
}

UdpClient::~UdpClient()
{

}

void UdpClient::onProcessPendingDatagrams()
{
    //receive data from tacos
    QByteArray datagram;

    QString str1="alarmon",str2="alarmoff",str3="opendoor",str4="closedoor";;
    mOnOffLineLineEdit->setText("Tacos alive");
//    if(str1==str2){
//       return true;
//    }
//    if(str1.compare(str2)==0)str3="opendoor",str4="closedoor"
//    {
//        return true;
//    }

    while(mUdpSocket.hasPendingDatagrams()) //是否有数据包等待读取
    {
        datagram.resize(mUdpSocket.pendingDatagramSize()); //
        mUdpSocket.readDatagram(datagram.data(), datagram.size());
    }
    qDebug()<<datagram;
    QString text;
    text = datagram.data();

    if(text.compare(str1)==0)//alarmon
    {
        mAlarmLineEdit->setText(str1);
        return;
    }
    if(text.compare(str2)==0)//alarmoff
    {
        mAlarmLineEdit->setText(str2);
        return;
    }
    if(text.compare(str3)==0)//opendoor
    {
        mDoorQComboBox->setCurrentIndex(0);
        return;
    }
    if(text.compare(str4)==0)//closedoor
    {
        mDoorQComboBox->setCurrentIndex(1);
        return;
    }

    mTacosReportTextEdit->append(datagram.data());
}

void UdpClient::on_mConnectPushButton_clicked()
{
    //send data to Tacos
    //qDebug()<<"test";
    QByteArray datagram;
    QHostAddress tacos_address;
    QString tacos_str_ip;
    datagram.append("data");
    tacos_str_ip = mIpLineEdit->text();
    tacos_address.setAddress(tacos_str_ip);
    int port = mPortLineEdit->text().toInt();
    mUdpSocket.writeDatagram(datagram,tacos_address,port);//send to which address and which port

}
void UdpClient::on_sel(const QString &text)
{
    //send data to Tacos
    //qDebug()<<"test";
    QByteArray datagram;
    QHostAddress tacos_address;
    QString tacos_str_ip;

    if(mDoorQComboBox->currentIndex()==0)
    {
        datagram.append("opendoor");
    }else
    {
        datagram.append("closedoor");
    }
    tacos_str_ip = mIpLineEdit->text();
    tacos_address.setAddress(tacos_str_ip);
    int port = mPortLineEdit->text().toInt();
    mUdpSocket.writeDatagram(datagram,tacos_address,port);//send to which address and which port
}
