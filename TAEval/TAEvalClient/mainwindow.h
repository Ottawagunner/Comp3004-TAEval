#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "server.h"
#include <QMainWindow>
#include "clientcontroller.h"
#include <QString>
class clientcontroller;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setController(clientcontroller*);
    void writeToLog(QString);
    
private slots:
    void on_runTestButton_clicked();
    void on_selectTestOption_highlighted(const int i);

private:
    QString options[9];
    Ui::MainWindow *ui;
    clientcontroller *controller;
    void writeToDescription(QString);
};

#endif // MAINWINDOW_H
