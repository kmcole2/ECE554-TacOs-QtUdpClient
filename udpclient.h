#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QtNetwork/QUdpSocket>

class UdpClient : public QDialog
{
    Q_OBJECT

public:
    UdpClient(QWidget *parent = 0);
    ~UdpClient();

private slots:
    void onProcessPendingDatagrams();

private slots:
void on_mConnectPushButton_clicked();


private slots:
    void on_sel(const QString &text);

private:
    QUdpSocket mUdpSocket;
    QLabel *mLocalIpAddress;
    QLabel *mLocalUdpPort;
    QLabel *mIpLabel;
    QLabel *mPortLabel;
    QLabel *mOnOffLineLabel;
    QLabel *mDoorLabel;
    QLabel *mAlarmLabel;

    QLineEdit *mIpLineEdit;
    QLineEdit *mPortLineEdit;
    QLineEdit *mOnOffLineLineEdit;
    QComboBox *mDoorQComboBox;
    QLineEdit *mAlarmLineEdit;

    QPushButton *mConnectPushButton;

    QTextEdit *mTacosReportTextEdit;
};

#endif // UDPCLIENT_H
