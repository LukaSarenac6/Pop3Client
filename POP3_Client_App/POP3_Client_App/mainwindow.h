#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QValidator>
#include "UserAuto.h"
#include "ClAuto.h"
#include "ChAuto.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

private slots:
    void on_pushButton_clicked();

    void on_quitButton_clicked();

    void on_statButton_clicked();

    void user_logged();

    void user_disconected(const QString& message);

    void on_retrButton_clicked();

    //void on_listButton_clicked();

    void on_deleButton_clicked();

    void stat_result(QString message);

    void username_password_incorrect();

    void print_mail_size(int size);

    void print_mail(QString mail);

    void no_mail_at_index();

    void mail_deleted(QString message);
private:
    Ui::MainWindow *ui;

    UserAuto *user;
    ClAuto *client;
    ChAuto *channel;
};
#endif // MAINWINDOW_H
