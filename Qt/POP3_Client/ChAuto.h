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
#include "const.h"
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
    void Channel_Signal_Client_Connection_Accept(const QString& message);
    void Channel_Signal_MSG_Response(const QString messageResponse);


public slots:
    void Channel_Slot_Client_Connection_Request(const QString& message);
    void Channel_Slot_Client_Username_Receive(const QString& message);


private:
    bool Channel_Username_Exists(const QString& username);
    ChStates channelState;
    const QString okMessage = "MSG(+OK)";
    const QString errMessage = "MSG(-ERR)";

};

#endif // CHAUTO_H
