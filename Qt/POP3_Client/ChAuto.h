#ifndef CHAUTO_H
#define CHAUTO_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <QFile>
#include <QByteArray>
#include <QString>
#include <QFile>
#include <QStringList>

class ChAuto : public QObject
{
    Q_OBJECT
public:
    enum ChStates {
        FSM_Ch_Idle,
        FSM_Ch_Connecting,
        FSM_Ch_Connected
    };

    explicit ChAuto(QObject *parent = nullptr);
    ~ChAuto();

signals:
    void Channel_Signal_Client_Connection_Accept(const QString&);
    void Channel_Signal_MSG_Response(const QString);
    //void Channel_Signal_Disconect_User(const QString&);


public slots:
    void Channel_Slot_Client_Connection_Request(const QString&);
    void Channel_Slot_Username_Receive(const QString&);
    void Channel_Slot_Password_Receive(const QString&);
    void Channel_Slot_MSG_Quit(const QString);
    void Channel_Slot_Stat_Message(const QString);

private:
    bool Channel_Username_Exists(const QString&);
    bool Channel_Password_Exists(const QString&);

    ChStates channelState;
    const QString okMessage = "MSG(+OK)";
    const QString errMessage = "MSG(-ERR)";

    QStringList userList;

};

#endif // CHAUTO_H
