#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "server.h"
#include <QMainWindow>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    QString options[9];
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Server client;
    std::string userName;
    
private slots:
    short handleLogIn();
    short handleLogOut();
    short handleCreateTask();
    short handleEditTask();
    short handleDeleteTask();
    short handleViewTask();
    short handleCreateEval();
    short handleViewTAs();
    short handleViewCourse();
    void on_runTestButton_clicked();

    void on_selectTestOption_highlighted(const int i);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
