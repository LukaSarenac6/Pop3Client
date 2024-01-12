#include "ChAuto.h"


ChAuto::ChAuto(QObject *parent) {
    channelState = FSM_Ch_Idle;
}

ChAuto::~ChAuto() {

}

bool ChAuto::Channel_Username_Exists(const QString& usernameMessage) {

    //TO DO: realizovati logiku provere
    return true;
}

void ChAuto::Channel_Slot_Client_Connection_Request(const QString& clientMessage) {
    //qDebug() << "Client message = " << clientMessage;

    if (clientMessage != "Cl_Connection_Request") {
        qDebug() << "ERROR MESSAGE INCORECT IN Channel_Slot_Client_Connection_Request";
    }

    /*TO DO realizovati tajmer sa nekom logikom random broja*/


    /*######################################################*/
    channelState = FSM_Ch_Connecting;

    const QString channelMessage = "Cl_Connection_Accept";
    //const QString channelMessageReject;

    emit Channel_Signal_Client_Connection_Accept(channelMessage);

    channelState = FSM_Ch_Connected;

}

void ChAuto::Channel_Slot_Client_Username_Receive(const QString& usernameMessage) {

    qDebug() << usernameMessage;

    if (!Channel_Username_Exists(usernameMessage)) {
        emit Channel_Signal_MSG_Response(errMessage);
        return;
    }

    emit Channel_Signal_MSG_Response(okMessage);

}

