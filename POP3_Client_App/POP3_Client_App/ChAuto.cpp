#include "ChAuto.h"


ChAuto::ChAuto(QObject *parent) {
    channelState = FSM_Ch_Idle;
}

ChAuto::~ChAuto() {

}

bool ChAuto::Channel_Username_Exists(const QString& usernameMessage) {


    QFile file("D:/7.semestar/MRKiRM/Projekat/userDatabase.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open the database file.";
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {

        QString line = in.readLine();
        QStringList userInfo = line.split(":");
        if (userInfo[0] == usernameMessage.split("(")[1].split(")")[0]) {
            /* since message is in format MSG(username), split it, after first split -> {MSG, username)}, after seccond split -> {username}*/

            /*put user info in a list of two elements {username, password}*/
            userList = userInfo;

            file.close();

            return true;
        }
    }

    file.close();
    return false;
}

bool ChAuto::Channel_Password_Exists(const QString& passwordMessage) {

    if (passwordMessage.split("(")[1].split(")")[0] == userList[1]) {
        return true;
    }
    return false;
}

void ChAuto::Channel_Slot_Client_Connection_Request(const QString& clientMessage) {
    //qDebug() << "Client message = " << clientMessage;

    if (clientMessage != "Cl_Connection_Request") {
        qDebug() << "ERROR MESSAGE INCORECT IN Channel_Slot_Client_Connection_Request";
    }

    /*TO DO realizovati tajmer sa nekom logikom random broja*/


    /*######################################################*/
    channelState = FSM_Ch_Connecting;

    const QString& channelMessage = "Cl_Connection_Accept";     /*menjanoo nesto pa ako baguje pogledaj ovde*/
    //const QString channelMessageReject;

    emit Channel_Signal_Client_Connection_Accept(channelMessage);

    channelState = FSM_Ch_Connected;

}

void ChAuto::Channel_Slot_Username_Receive(const QString& usernameMessage) {

    qDebug() << usernameMessage;

    if (!Channel_Username_Exists(usernameMessage)) {
        emit Channel_Signal_MSG_Response(errMessage);
        return;
    }

    emit Channel_Signal_MSG_Response(okMessage);

}

void ChAuto::Channel_Slot_Password_Receive(const QString& passwordMessage) {
    qDebug() << passwordMessage;

    if (!Channel_Password_Exists(passwordMessage)) {
        emit Channel_Signal_MSG_Response(errMessage);
        return;
    }

    emit Channel_Signal_MSG_Response(okMessage);
}

void ChAuto::Channel_Slot_MSG_Quit(const QString quitMessage) {
    qDebug() << quitMessage;    /*TO DO PROVERA DA LI JE DOBRA PORUKA*/
    const QString& disconectMessage = "Cl_Disconected";
    emit Channel_Signal_MSG_Response(disconectMessage);
    channelState = FSM_Ch_Idle;
}

void ChAuto::Channel_Slot_Stat_Message(const QString statMessage) {
    qDebug() << statMessage;
    // positive = +OK numOfMessages sizeOfMaildrop(in octets)
    // izbrisane poruke se ne broje

    QDir directory("D:/7.semestar/MRKiRM/Projekat/mails");

    if (!directory.exists())    {
        qWarning() << "Directory does not exist: " << "D:/7.semestar/MRKiRM/Projekat/mails";
        return;
    }

    QStringList filters;
    filters << "*.txt";
    // Filter the files in the directory based on the ".txt" extension
    directory.setNameFilters(filters);
    // Get the list of files matching the filter
    QFileInfoList fileList = directory.entryInfoList();

    qint16 mailNum = 0;

    mailNum = fileList.size();
    qint64 mailSize = 0;

    foreach(const QFileInfo& file, fileList) {
        mailSize += file.size();
    }


    QString statResult = "+OK " + QString::number(mailNum) + " " + QString::number(mailSize) /*+ "\r\n"*/;
    emit Channel_Signal_Stat_Result(statResult);
    qDebug() << statResult;

    return;
}

void ChAuto::Channel_Slot_List_Message(const QString& message) {
    // opcioni argument (ako zelimo samo jednu poruku da izlistamo i vidimo njenu velicinu)
    // +OK brojPoruka messages (velicina octets)
    // redniBrojPoruke velicina
    // ..... za sve poruke
    qDebug() << message;
}

void ChAuto::Channel_Slot_Retr_Message(const QString& message){
    // obavezan argument (koju poruku zelimo da procitamo)
    // +OK velicina octets
    // mail
    // -ERR no such message
    QDir directory("D:/7.semestar/MRKiRM/Projekat/mails");

    // Ensure that the directory exists
    if (!directory.exists()) {
        qWarning() << "Directory does not exist: " << "D:/7.semestar/MRKiRM/Projekat/mails";
        return;
    }

    // Filter the files in the directory based on the ".txt" extension
    QStringList nameFilters;
    nameFilters << "*.txt";
    directory.setNameFilters(nameFilters);

    // Get the list of files matching the filter
    QFileInfoList fileList = directory.entryInfoList();


}


void ChAuto::Channel_Slot_Dele_Message(const QString& message){
    // obavezan argument (koju poruku brisemo)
    // poruka je oznacena kao obrisana, sve sto dalje pokusamo sa njom vraca error
    // +OK message brojPorukeKojuBrisemo deleted
    // -ERR message brojPoruke alread deleted
    qDebug() << message;
}

/*ako stignem uraditi i rset i noop*/

