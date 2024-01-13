#ifndef USERAUTO_H
#define USERAUTO_H


#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QByteArray>
#include <QString>
#include <QTextStream>
#include <QCoreApplication>



class UserAuto : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief The UserStates enum shows the states that the User automat can be in
     */
    enum UserStates {
        FSM_User_Idle,
        FSM_User_Connecting,
        FSM_User_Connected
    };

    explicit UserAuto(QObject *parent = nullptr);
    ~UserAuto();

    /**
     * @brief a function that beggins users access to mail through POP3
     */
    void User_Set_All();

signals:
    /**
     * @brief sends the message to begin the mail check, connected with SLOT Client_Slot_User_Check_Mail
     * @param message "User_Check_Mail" of POP3 protocol
     */
    void User_Signal_Set_All(const QString& message);
    /**
     * @brief signal emited when user connection is established, connected with SLOT User_Slot_User_Connected
     */
    void User_Signal_User_Connected();
    /**
     * @brief when emited sends username and password entered by the user, connected with SLOT Client_Slot_User_Sent_Username_Password
     * @param username
     * @param password
     */
    void User_Signal_Send_Username_Password(const QString& username, const QString& password);


public slots:

    /**
     * @brief checks client message to se if connection is established, connected with SIGNAL Client_Signal_User_Connection
     * @param message from client -> "User_Connected" of POP3 protocol
     */
    void User_Slot_User_Connection(const QString& message);
    /**
     * @brief gets username and password through input, connected with SIGNAL User_Signal_User_Connected
     */
    void User_Slot_User_Connected();

    /**
     * @brief disconects the user changing his state to Idle, connected with SIGNAL Client_Signal_User_Disconected
     * @param message from client -> "User_Disconected" of POP3 protocol
     */
    void User_Slot_User_Disconected(const QString& message);


private:
    /**
     * @brief represents the current state of the user automate
     */
    UserStates userState;
};

#endif // USERAUTO_H
