#ifndef USERAUTO_H
#define USERAUTO_H


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
#include <QTextStream>
#include <iostream>
#include <QCoreApplication>
#include <string>
#include "const.h"

class UserAuto : public QObject
{
    Q_OBJECT
public:
    enum UserStates {
        FSM_User_Idle,
        FSM_User_Connecting,
        FSM_User_Connected
    };



    explicit UserAuto(QObject *parent = nullptr);
    ~UserAuto();

    void User_Set_All();

signals:
    void User_Signal_Set_All(const QString& message);
    void User_Signal_User_Connected();
    void User_Signal_Send_Username_Password(const QString& username, const QString& password);


public slots:
    void User_Slot_User_Connection(const QString& message);
    void User_Slot_User_Connected();


private:
    UserStates userState;
};

#endif // USERAUTO_H
