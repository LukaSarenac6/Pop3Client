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

    void Channel_Signal_Stat_Result(QString message);
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
     * @brief activated when client sends a STAT message DOPISATI SUTRA
     * @param messgage "MSG(STAT)" of POP3 protocol
     */
    void Channel_Slot_Stat_Message(const QString message);
    void Channel_Slot_Retr_Message(const QString& message);
    void Channel_Slot_List_Message(const QString& message);
    void Channel_Slot_Dele_Message(const QString& message);

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
