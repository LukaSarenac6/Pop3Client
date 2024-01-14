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
    ui->retrButton->setDisabled(true);
    ui->deleButton->setDisabled(true);
    ui->listButton->setDisabled(true);
    ui->textEdit->setReadOnly(true);
    ui->lineEditList->setDisabled(true);
    ui->lineEditRetr->setDisabled(true);

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
    QObject::connect(client, SIGNAL(Client_Signal_Send_Retr(QString)), channel, SLOT(Channel_Slot_Retr_Message(QString)));
    QObject::connect(client, SIGNAL(Client_Signal_Send_List(QString)), channel, SLOT(Channel_Slot_List_Message(QString)));
    QObject::connect(client, SIGNAL(Client_Signal_Send_Dele(QString)), channel, SLOT(Channel_Slot_Dele_Message(QString)));
    QObject::connect(channel, SIGNAL(Channel_Signal_Stat_Result(QString)), client, SLOT(Client_Slot_Stat_Result(QString)));
    QObject::connect(client, SIGNAL(Client_Signal_Stat_Result(QString)), this, SLOT(stat_result(QString)));
    QObject::connect(client, SIGNAL(Client_Signal_Username_Password_Incorrect()), this, SLOT(username_password_incorrect()));
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
    emit client->Client_Signal_MSG_Quit("MSG(QUIT)");    // TO DO: PROVERU DA LI MOZE DA PRIMI TAKVU PORUKU U TOM STANJU
}


void MainWindow::on_statButton_clicked()
{
    emit client->Client_Signal_Send_Stat("MSG(STAT)");
}

void MainWindow::user_logged() {
    ui->textEdit->clear();
    ui->textEdit->insertPlainText("Welcome!");

    ui->lineEditList->setDisabled(false);
    ui->lineEditRetr->setDisabled(false);
    ui->pushButton->setDisabled(true);
    ui->quitButton->setEnabled(true);
    ui->statButton->setEnabled(true);
    ui->retrButton->setEnabled(true);
    ui->deleButton->setEnabled(true);
    ui->listButton->setEnabled(true);
}

void MainWindow::user_disconected(const QString& message) {
    ui->pushButton->setDisabled(false);
    ui->quitButton->setEnabled(false);
    ui->statButton->setEnabled(false);
    ui->statButton->setEnabled(false);
    ui->retrButton->setEnabled(false);
    ui->deleButton->setEnabled(false);
    ui->listButton->setEnabled(false);
    ui->lineEditList->setDisabled(true);
    ui->lineEditRetr->setDisabled(true);

}



void MainWindow::on_retrButton_clicked()
{
    emit client->Client_Signal_Send_Retr("MSG(RETR) " + ui->lineEditRetr->text());
    client->SetState(ClAuto::FSM_Cl_Receiving);
}


void MainWindow::on_listButton_clicked()
{
    // TO DO: realizovati za prosledjivanje argumenata i proveru u kom je stanju pa da li moze slati ovo
    emit  client->Client_Signal_Send_List("MSG(LIST)");
    client->SetState(ClAuto::FSM_Cl_Receiving);
}


void MainWindow::on_deleButton_clicked()
{
    emit client->Client_Signal_Send_Dele("MSG(DELE)");
    client->SetState(ClAuto::FSM_Cl_Deleting);
}

void MainWindow::stat_result(QString statResult){

    ui->textEdit->clear();
    ui->textEdit->insertPlainText("Num of messages = " + statResult.split(" ")[1] + "\nSize = " + statResult.split(" ")[2]);
}

void MainWindow::username_password_incorrect() {
    ui->textEdit->clear();
    ui->textEdit->insertPlainText("Ussername or Password are incorrect!");
}

