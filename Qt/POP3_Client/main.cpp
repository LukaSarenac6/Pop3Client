#include <QCoreApplication>
#include "ChAuto.h"
#include "ClAuto.h"
#include "UserAuto.h"


int main(int argc, char *argv[])
{

    qDebug() << " POCETAK ";
    QCoreApplication a(argc, argv);

    // TO DO: realizovati connect unutar konstruktora
    UserAuto user;
    ClAuto client;
    ChAuto channel;

    QObject::connect(&user, SIGNAL(User_Signal_Set_All(QString)), &client, SLOT(Client_Slot_User_Check_Mail(QString)));
    QObject::connect(&client, SIGNAL(Client_Signal_Connection_Request(QString)), &channel, SLOT(Channel_Slot_Client_Connection_Request(QString)));
    QObject::connect(&channel, SIGNAL(Channel_Signal_Client_Connection_Accept(QString)), &client, SLOT(Client_Slot_Channel_Connection_Accept(QString)));
    QObject::connect(&client, SIGNAL(Client_Signal_User_Connection(QString)), &user, SLOT(User_Slot_User_Connection(QString)));
    QObject::connect(&user, SIGNAL(User_Signal_User_Connected()), &user, SLOT(User_Slot_User_Connected()));
    QObject::connect(&user, SIGNAL(User_Signal_Send_Username_Password(QString,QString)), &client, SLOT(Client_Slot_User_Sent_Username_Password(QString,QString)));
    QObject::connect(&client, SIGNAL(Client_Signal_Send_Username(QString)), &channel, SLOT(Channel_Slot_Client_Username_Receive(QString)));
    QObject::connect(&channel, SIGNAL(Channel_Signal_MSG_Response(QString)), &client, SLOT(Client_Slot_Channel_MSG_Response(QString)));
    QObject::connect(&client, SIGNAL(Client_Signal_Username_Ok(QString, QString)), &client, SLOT(Client_Slot_User_Sent_Username_Password(QString, QString)));

    user.User_Set_All();

    return a.exec();
}
