#include "UserAuto.h"

UserAuto::UserAuto(QObject *parent) {
    userState = FSM_User_Idle;
}

UserAuto::~UserAuto() {

}


void UserAuto::User_Set_All(const QString& username, const QString& password) {
    this->username = username;
    this->password = password;
    const QString& message = "User_Check_Mail";
    qDebug() << "dal udje ovde";
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

    const QString& usernameToSend = username;
    const QString& passwordToSend = password;
    // TO DO: unos sa tastature
    emit User_Signal_Send_Username_Password(usernameToSend, passwordToSend);

    userState = FSM_User_Connected;

}

void UserAuto::User_Slot_User_Disconected(const QString& disconectMessage) {
    qDebug() << disconectMessage;

    userState = FSM_User_Idle;
}
