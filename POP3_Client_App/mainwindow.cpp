#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    user(new UserAuto(this)),
    client(new ClAuto(this)),
    channel(new ChAuto(this))

{
    ui->setupUi(this);

    ui->quitButton->setDisabled(true);
    ui->statButton->setDisabled(true);


    QObject::connect(user, SIGNAL(User_Signal_Set_All(QString)), client, SLOT(Client_Slot_User_Check_Mail(QString)));
    QObject::connect(client, SIGNAL(Client_Signal_Connection_Request(QString)), channel, SLOT(Channel_Slot_Client_Connection_Request(QString)));
    QObject::connect(channel, SIGNAL(Channel_Signal_Client_Connection_Accept(QString)), client, SLOT(Client_Slot_Channel_Connection_Accept(QString)));
    QObject::connect(client, SIGNAL(Client_Signal_User_Connection(QString)), user, SLOT(User_Slot_User_Connection(QString)));
    QObject::connect(user, SIGNAL(User_Signal_User_Connected()), user, SLOT(User_Slot_User_Connected()));
    QObject::connect(user, SIGNAL(User_Signal_Send_Username_Password(QString,QString)), client, SLOT(Client_Slot_User_Sent_Username_Password(QString,QString)));
    QObject::connect(client, SIGNAL(Client_Signal_Send_Username(QString)), channel, SLOT(Channel_Slot_Username_Receive(QString)));
    QObject::connect(channel, SIGNAL(Channel_Signal_MSG_Response(QString)), client, SLOT(Client_Slot_Channel_MSG_Response(QString)));
    QObject::connect(client, SIGNAL(Client_Signal_Username_Password_Ok(QString,QString)), client, SLOT(Client_Slot_User_Sent_Username_Password(QString,QString)));
    QObject::connect(client, SIGNAL(Client_Signal_Send_Password(QString)), channel, SLOT(Channel_Slot_Password_Receive(QString)));
    QObject::connect(client, SIGNAL(Client_Signal_MSG_Quit(QString)), channel, SLOT(Channel_Slot_MSG_Quit(QString)));
    QObject::connect(client, SIGNAL(Client_Signal_User_Disconected(QString)), user, SLOT(User_Slot_User_Disconected(QString)));
    QObject::connect(client, SIGNAL(Client_Signal_Send_Stat(QString)), channel, SLOT(Channel_Slot_Stat_Message(QString)));
    QObject::connect(client, SIGNAL(Client_Signal_User_Logged()), this, SLOT(user_logged()));
    QObject::connect(client, SIGNAL(Client_Signal_User_Disconected(QString)), this, SLOT(user_disconected(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "jel se klikne";
    /*UserAuto user;
    ClAuto client;
    ChAuto channel;*/

    QString username = ui->username->text();
    QString password = ui->password->text();
    qDebug() << username + password;
    user->User_Set_All(username, password);

}

void MainWindow::on_quitButton_clicked()
{
    client->emit Client_Signal_MSG_Quit("MSG(QUIT)");    // TO DO: PROVERU DA LI MOZE DA PRIMI TAKVU PORUKU U TOM STANJU
}


void MainWindow::on_statButton_clicked()
{
    client->emit Client_Signal_Send_Stat("MSG(STAT)");
}

void MainWindow::user_logged() {
    ui->pushButton->setDisabled(true);
    ui->quitButton->setEnabled(true);
    ui->statButton->setEnabled(true);
}

void MainWindow::user_disconected(const QString& message) {
    ui->pushButton->setDisabled(false);
    ui->quitButton->setEnabled(false);
    ui->statButton->setEnabled(false);
}


