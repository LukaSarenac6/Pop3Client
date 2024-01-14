#include "ClAuto.h"

ClAuto::ClAuto(QObject *parent) {
    clientState = FSM_Cl_Ready;
}

ClAuto::~ClAuto() {

}

void ClAuto::SetState(ClStates state) {
    this->clientState = state;
}

QString ClAuto::Client_Make_Message(QString& string) {

    QString message = "MSG(" + string + ")";
    return message;
}

void ClAuto::Client_Slot_User_Check_Mail(const QString& userMessage) {
    //qDebug() << "Received message = " << userMessage;

    // Check if message is correct
    if (userMessage != "User_Check_Mail") {
        qDebug() << "ERROR MESSAGE INCORRECT IN Client_Slot_User_Check_Mail";
        return;
    }

    const QString clientMessage = "Cl_Connection_Request";

    emit Client_Signal_Connection_Request(clientMessage);

    clientState = FSM_Cl_Connecting;
}

void ClAuto::Client_Slot_Channel_Connection_Accept(const QString& channelMessage) {
    //qDebug() << "Channel message = " << channelMessage;
    QString clientMessage;

    if (channelMessage == "Cl_Connection_Reject") {
        clientMessage = "User_Connection_Fail";

        emit Client_Signal_User_Connection(clientMessage);

        clientState = FSM_Cl_Ready;
    } else if (channelMessage == "Cl_Connection_Accept") {
        clientMessage = "User_Connected";

        emit Client_Signal_User_Connection(clientMessage);

        clientState = FSM_Cl_Authorising;
    } else {
        qDebug() << "ERROR MESSAGE INCORECT IN Client_Slot_Channel_Connection_Accept";
    }
}

void ClAuto::Client_Slot_User_Sent_Username_Password(const QString& username, const QString& password) {

    if (!usernameSent) {
        qDebug() << username;
        qDebug() << password;

        usernameReceived = username;
        passwordReceived = password;
    }

    QString usernameMessage = usernameReceived;
    QString passwordMessage = passwordReceived;

    if (!usernameSent) {
        usernameSent = true;

        usernameMessage = Client_Make_Message(usernameMessage);
        qDebug() << usernameMessage;

        emit Client_Signal_Send_Username(usernameMessage);

        clientState = FSM_Cl_User_Check;
        return;
    }

    if (!passwordSent) {
        passwordSent = true;

        passwordMessage = Client_Make_Message(passwordMessage);
        qDebug() << passwordMessage;

        emit Client_Signal_Send_Password(passwordMessage);
        clientState = FSM_Cl_Pass_Check;
        return;
    }
    emit Client_Signal_User_Logged();
    //qDebug() << "za sad radi dobro";
    //const QString& statMessage = "MSG(STAT)";
    //emit Client_Signal_Send_Stat(statMessage);
    clientState = FSM_Cl_Mail_Check;
}

void ClAuto::Client_Slot_Channel_MSG_Response(const QString messageResponse) {
    qDebug() << messageResponse;
    if (messageResponse == "MSG(-ERR)") {
        // TO DO: MSG QUIT
        emit Client_Signal_Username_Password_Incorrect();
        usernameSent = false;
        passwordSent = false;
        qDebug() << quitMessage;
        emit Client_Signal_MSG_Quit(quitMessage);
        clientState = FSM_Cl_Disconnecting;
        return;
    } else if (messageResponse == "Cl_Disconected") {
        const QString& disconectMessage = "User_Disconected";
        emit Client_Signal_User_Disconected(disconectMessage);
        clientState = FSM_Cl_Ready;
        return;
    }

    emit Client_Signal_Username_Password_Ok(usernameReceived, passwordReceived);
}

void ClAuto::Client_Slot_Stat_Result(QString statResult) {
    qDebug() << statResult;
    emit Client_Signal_Stat_Result(statResult);
}

