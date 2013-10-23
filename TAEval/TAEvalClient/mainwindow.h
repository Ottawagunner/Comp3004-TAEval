#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_createTaskButton_clicked();

    void on_editTaskButton_clicked();

    void on_deleteTaskButton_clicked();

    void on_viewCoursesButton_clicked();

    void on_viewAsignedTasks_clicked();

    void on_viewTAButton_clicked();

    void on_loginButton_clicked();

    void on_logoutButton_clicked();

    void on_giveEvaluationButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
