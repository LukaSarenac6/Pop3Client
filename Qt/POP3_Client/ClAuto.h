#ifndef CLAUTO_H
#define CLAUTO_H


#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <QFile>
#include <QByteArray>
#include <QString>
#include "const.h"
class ClAuto : public QObject
{
    Q_OBJECT
public:
    enum ClStates {
        FSM_Cl_Ready,
        FSM_Cl_Connecting,
        FSM_Cl_Authorising,
        FSM_Cl_User_Check,
        FSM_Cl_Pass_Check,
        FSM_Cl_Receiving,
        FSM_Cl_Mail_Check,
        FSM_Cl_Deleting,
        FSM_Cl_Disconnecting
    };

    explicit ClAuto(QObject *parent = nullptr);
    ~ClAuto();


signals:
    void Client_Signal_Connection_Request(const QString&);
    void Client_Signal_User_Connection(const QString&);
    void Client_Signal_Send_Username(const QString&);
    void Client_Signal_Username_Ok(const QString&, const QString&);

public slots:
    void Client_Slot_User_Check_Mail(const QString& message);
    void Client_Slot_Channel_Connection_Accept(const QString& message);
    void Client_Slot_User_Sent_Username_Password(const QString& username, const QString& password);
    void Client_Slot_Channel_MSG_Response(const QString messageResponse);

private:
    QString Client_Make_Message(QString& string);

    ClStates clientState;
    bool usernameSent = false;

    QString usernameReceived;
    QString passwordReceived;
};


#endif // CLAUTO_H
