#include "UserAuto.h"

UserAuto::UserAuto(QObject *parent) {
    userState = FSM_User_Idle;
}

UserAuto::~UserAuto() {

}


void UserAuto::User_Set_All() {
    const QString& message = "User_Check_Mail";

    emit User_Signal_Set_All(message);

    userState = FSM_User_Connecting;
}

void UserAuto::User_Slot_User_Connection(const QString& clientMessage){
    //qDebug() <<"Client message = " << clientMessage;
    if (clientMessage == "User_Connection_Fail") {
        qDebug() << "CONNECTION REJECTED";
        userState = FSM_User_Idle;
        return;
    }

    emit User_Signal_User_Connected();
}

void UserAuto::User_Slot_User_Connected() {

    const QString& username = "luka";
    const QString& password = "sarenac";
    // TO DO: unos sa tastature
    emit User_Signal_Send_Username_Password(username, password);

    userState = FSM_User_Connected;

}

void UserAuto::User_Slot_User_Disconected(const QString& disconectMessage) {
    qDebug() << disconectMessage;
    userState = FSM_User_Idle;
}
