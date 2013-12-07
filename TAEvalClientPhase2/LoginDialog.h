#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <QDialog>
#include <string>
#include "uicontroller.h"

class QRadioButton;
class QLabel;
class QPushButton;
class QLineEdit;
class QGroupBox;
class UIController;

class LoginDialog : public QDialog{
    Q_OBJECT

public:
    LoginDialog(UIController *cont,QWidget *parent=0);
    void getUserInfo(std::string*, char*);
    void clearInfo();
private slots:
    void loginButtonClicked();
    void quitButtonClicked();
private:
    std::string username;
    char   userType;
    UIController *c;
    QLabel *loginLabel;
    QPushButton *loginButton;
    QPushButton *quitButton;
    QLineEdit *unameField;
    QRadioButton *taOption;
    QRadioButton *instructorOption;
    QGroupBox *group;
    virtual void closeEvent(QCloseEvent *e);
};

#endif // LOGINDIALOG_H
