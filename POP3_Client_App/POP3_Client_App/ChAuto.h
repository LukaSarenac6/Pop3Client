#ifndef CHAUTO_H
#define CHAUTO_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QByteArray>
#include <QString>
#include <QFile>
#include <QStringList>
#include <QDir>

class ChAuto : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief The ChStates enum shows the states that the User automat can be in
     */
    enum ChStates {
        FSM_Ch_Idle,
        FSM_Ch_Connecting,
        FSM_Ch_Connected
    };

    explicit ChAuto(QObject *parent = nullptr);
    ~ChAuto();

signals:

    /**
     * @brief send a message to the client telling him that the connection is accepted, connected to SLOT Client_Slot_Channel_Connection_Accept
     * @param message "Cl_Connection_Accept" of the POP3 protocol
     */
    void Channel_Signal_Client_Connection_Accept(const QString& message);

    /**
     * @brief a response to a client message, the response depends on the clients request, connected to SLOT Client_Slot_Channel_MSG_Response
     * @param message
     */
    void Channel_Signal_MSG_Response(const QString message);
    //void Channel_Signal_Disconect_User(const QString&);

    /**
     * @brief provides the stat result the the channel, connected with SLOT Client_Slot_Stat_Result
     * @param message, stat resul
     */
    void Channel_Signal_Stat_Result(QString message);

    /**
     * @brief emits the size of the mail at specific index when user presses retr, connected with SLOT Client_Slot_Mail_Size
     * @param message, size of the mail
     */
    void Channel_Signal_Mail_Size(QString message);
    /**
     * @brief emits the content of the mail at specific index when user presses retr, connected with SLOT Client_Slot_Mail_Content
     * @param message, mail content
     */
    void Channel_Signal_Mail_Content(QString message);
    /**
     * @brief emits an error that there is no mail at index, connected with SLOT Client_Slot_No_Mail_At_Index
     * @param message, "MSG(-ERR) of POP3 protocol
     */
    void Channel_Signal_No_Mail_At_Index(QString message);
    /**
     * @brief emits a successful mail delition, connected with SLOT Client_Slot_Mail_Dele
     * @param message
     */
    void Channel_Signal_Mail_Deleted(QString message);
public slots:
    /**
     * @brief establishes the connection which can be manualy approwed in code, connected to SIGNAL Client_Signal_Connection_Request
     * @param message "Cl_Connection_Request" of POP3 protocol
     */
    void Channel_Slot_Client_Connection_Request(const QString& message);
    /**
     * @brief receives the username and returns a valid message to the user based on the username existence, connected to SIGNAL Client_Signal_Send_Username
     * @param username
     */
    void Channel_Slot_Username_Receive(const QString& username);
    /**
     * @brief receives the password and returns a valid message to the user based on the password existance, connected to SIGNAL Client_Signal_Send_Password
     * @param password
     */
    void Channel_Slot_Password_Receive(const QString& password);
    /**
     * @brief activated when client sends a QUIT message, proceeds to disconect the user, connected to SIGNAL Client_Signal_MSG_Quit
     * @param message "MSG(Quit)" of POP3 protocol
     */
    void Channel_Slot_MSG_Quit(const QString message);
    /**
     * @brief counts the number of mails and size of all mails, connected with SIGNAL Client_Signal_Send_Stat
     * @param message "MSG(STAT)" of POP3 protocol
     */
    void Channel_Slot_Stat_Message(const QString message);
    /**
     * @brief checks if there is a mail at provided index and emits two signals, one with the mail size, other with mail content,
     *  if there is no meil with provided intex emit -ERR,  connected with SIGNAL Client_Signal_Send_Retr
     * @param message
     */
    void Channel_Slot_Retr_Message(const QString& message);

    /**
     * @brief delets the mail at the provided index, if there is no mail at index emit -ERR signal, connected with SIGNAL Client_Signal_Send_Dele
     * @param message
     */
    void Channel_Slot_Dele_Message(const QString& message);

    //void Channel_Slot_List_Message(const QString& message);

private:
    /**
     * @brief finds user info in the userDatabase and checks if the entered username exists
     * @param username
     * @return true if exist, false if doesnt
     */
    bool Channel_Username_Exists(const QString& username);
    /**
     * @brief checks if the password corresponds to the given username
     * @param password
     * @return true if does, false if doesnt
     */
    bool Channel_Password_Exists(const QString& password);

    ChStates channelState;
    /**
     * @brief errMessage message of POP3 protocol
     */
    const QString okMessage = "MSG(+OK)";
    /**
     * @brief errMessage message of POP3 protocol
     */
    const QString errMessage = "MSG(-ERR)";

    /**
     * @brief a list of 2 elements containing username and password
     */
    QStringList userList;


};

#endif // CHAUTO_H
