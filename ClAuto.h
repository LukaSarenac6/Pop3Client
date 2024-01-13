#ifndef CLAUTO_H
#define CLAUTO_H


#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QByteArray>
#include <QString>

class ClAuto : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief The ClStates enum shows the states that the User automat can be in
     */
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
    /**
     * @brief send a message to channel to connect the user, connected to SLOT Channel_Slot_Client_Connection_Request
     * @param message "Cl_Connection_Request" of POP3 protocol
     */
    void Client_Signal_Connection_Request(const QString& message);
    /**
     * @brief send a accept or reject connection message, connected to SLOT User_Slot_User_Connection
     * @param message "User_Connection_Fail" or "User_Connected" of POP3 protocol
     */
    void Client_Signal_User_Connection(const QString& message);
    /**
     * @brief sends the username provided by the user to the channel, connected to SLOT Channel_Slot_Username_Receive
     * @param username
     */
    void Client_Signal_Send_Username(const QString& username);
    /**
     * @brief when username or password are correct proceeds the protocol, connected to SLOT Client_Slot_User_Sent_Username_Password
     * @param username, stored username
     * @param password, stored password
     */
    void Client_Signal_Username_Password_Ok(const QString& username, const QString& password);
    /**
     * @brief sends the password provided by the user to the channel, connected to SLOT Channel_Slot_Password_Receive
     * @param password
     */
    void Client_Signal_Send_Password(const QString& password);
    /**
     * @brief send a quit message to the channel, connected to SLOT Channel_Slot_MSG_Quit
     * @param message "MSG(Quit)" of POP3 protocol
     */
    void Client_Signal_MSG_Quit(const QString message);
    /**
     * @brief sends a disconect confirmation to the user, connected to SLOT User_Slot_User_Disconected
     * @param message "User_Disconected" of POP3 protocol
     */
    void Client_Signal_User_Disconected(const QString& message);
    /**
     * @brief sends a stat message to channel, connected to SLOT Channel_Slot_Stat_Message
     * @param message "MSG(STAT)" of POP3 protocol
     */
    void Client_Signal_Send_Stat(const QString& message);

public slots:
    /**
     * @brief receives a check mail message and proceeds the communication, connected to SIGNAL User_Signal_Set_All
     * @param message "User_Check_Mail" of POP3 protocol
     */
    void Client_Slot_User_Check_Mail(const QString& message);
    /**
     * @brief checks if channel sent a accept or reject connection confirmation message and continues the protocol based on the message, connected to SIGNAL Channel_Signal_Client_Connection_Accept
     * @param message "Cl_Connection_Accept" or "Cl_Connection_Reject" of POP3 protocol
     */
    void Client_Slot_Channel_Connection_Accept(const QString& message);
    /**
     * @brief makes sure to send username first, waits for confirmation and then sends password to channel, connected to SIGNAL User_Signal_Send_Username_Password and Client_Signal_Username_Password_Ok
     * @param username
     * @param password
     */
    void Client_Slot_User_Sent_Username_Password(const QString& username, const QString& password);
    /**
     * @brief composes a message needed for the current state of the protocol, connected to SIGNAL Channel_Signal_MSG_Response
     * @param message some type of POP3 protocol message
     */
    void Client_Slot_Channel_MSG_Response(const QString message);
    //void Client_Slot_Client_Disconected(const QString&);

private:
    /**
     * @brief makes a POP3 protocol message concatenating string with MSG()
     * @param string
     * @return MSG(STRING)
     */
    QString Client_Make_Message(QString& string);
    /**
     * @brief represents the current client automate
     */
    ClStates clientState;
    /**
     * @brief if username was already send, ensure that it wont happen again
     */
    bool usernameSent = false;
    /**
     * @brief if password was already send, ensure that it wont happen again
     */
    bool passwordSent = false;
    /**
     * @brief for saving username
     */
    QString usernameReceived;
    /**
     * @brief for saving passwor
     */
    QString passwordReceived;
    /**
     * @brief a message type in POP3 protocol
     */
    const QString quitMessage = "MSG(QUIT)";
};


#endif // CLAUTO_H
