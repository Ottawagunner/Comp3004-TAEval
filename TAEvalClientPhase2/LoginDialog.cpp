#include <QtGui>
#include "LoginDialog.h"
#include <iostream>

LoginDialog::LoginDialog(UIController *cont,QWidget *parent) : QDialog(parent){

    c = cont;
    loginLabel = new QLabel("UserName: ");
    loginButton = new QPushButton("Login");
    loginButton->setDefault(true);
    quitButton = new QPushButton("Quit");
    unameField = new QLineEdit;
    taOption = new QRadioButton("TA");
    instructorOption = new QRadioButton("Instructor");
    taOption->setChecked(true);
    group = new QGroupBox("Select User Type");

    connect(loginButton,SIGNAL(clicked()),this,SLOT(loginButtonClicked()));
    connect(quitButton,SIGNAL(clicked()),this,SLOT(quitButtonClicked()));

    QVBoxLayout *topLeft = new QVBoxLayout;
    topLeft->addWidget(loginLabel);
    topLeft->addWidget(unameField);
    topLeft->addStretch();

    QVBoxLayout *rButtonLayout = new QVBoxLayout;
    rButtonLayout->addWidget(taOption);
    rButtonLayout->addWidget(instructorOption);

    QVBoxLayout *leftSide = new QVBoxLayout;
    leftSide->addLayout(topLeft);
    leftSide->addLayout(rButtonLayout);

    QVBoxLayout *topRight = new QVBoxLayout;
    topRight->addWidget(loginButton);
    topRight->addWidget(quitButton);
    topRight->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftSide);
    mainLayout->addLayout(topRight);
    setLayout(mainLayout);

    setWindowTitle("Login");
}
void LoginDialog::loginButtonClicked(){
    username = unameField->text().toStdString();
    if(username.compare("")!=0){
        if(taOption->isChecked())
            userType = "t";
        else
            userType = "i";
        c->loginNotify();
        LoginDialog::close();
    }
}
void LoginDialog::quitButtonClicked(){
    QApplication::quit();
}
void LoginDialog::closeEvent(QCloseEvent *e){
        std::cout<<"CLOSED"<<std::endl;
        e->ignore();
}
void LoginDialog::getUserInfo(std::string *name, std::string *type){
    *name = username;
    *type = userType;
}
void LoginDialog::clearInfo(){
    username = "";
    userType = "t";
    unameField->setText("");
    taOption->setChecked(true);
}
