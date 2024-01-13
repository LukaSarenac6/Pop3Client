#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;

    UserAuto *user;
    ClAuto *client;
    ChAuto *channel;
};
#endif // MAINWINDOW_H
