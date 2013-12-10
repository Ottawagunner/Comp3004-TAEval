#include "ViewIndividualDialog.h"
#include<QtGui>
#include "prevententer.h"

ViewIndividualDialog::ViewIndividualDialog(viewTemplate *viewParent, viewIndividualType yourType, QWidget*)
{
    myParent = viewParent;
    type = yourType;
    listLabel = new QLabel("");
    closeButton = new QPushButton("Cancel");
    saveButton = new QPushButton("Save");
    additionalInfo = new QLineEdit;
    mainBody = new QTextEdit;

    connect(closeButton,SIGNAL(clicked()),this,SLOT(handleCloseButton()));
    connect(saveButton,SIGNAL(clicked()),this,SLOT(handleSaveButton()));
    PreventEnter *p = new PreventEnter();
    mainBody->installEventFilter(p);
    QVBoxLayout *main = new QVBoxLayout;
    main->addWidget(listLabel);
    main->addWidget(additionalInfo);
    main->addWidget(mainBody);
    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addWidget(closeButton);
    buttons->addWidget(saveButton);
    main->addLayout(buttons);
    setLayout(main);
    mainBody->setReadOnly(false);
    additionalInfo->setReadOnly(false);

    switch(type){
    case INSTRUCT_ADD_TASK:
        listLabel->setText("Add new task:");
        break;

    case INSTRUCT_ADD_EVAL:
        listLabel->setText("Add new evaluation:");
        break;

    case INSTRUCT_EDIT_TASK:
        listLabel->setText("Edit a task:");
        additionalInfo->setReadOnly(true);
        break;

    case INSTRUCT_EDIT_EVAL:
        listLabel->setText("Edit an evaluation:");
        break;

    case INSTRUCT_DETAIL_TASK:
        listLabel->setText("Viewing a task:");
        saveButton->setEnabled(false);
        mainBody->setReadOnly(true);
        additionalInfo->setReadOnly(true);
        break;

    case INSTRUCT_DETAIL_EVAL:
        listLabel->setText("Viewing an evaluation:");
        saveButton->setEnabled(false);
        mainBody->setReadOnly(true);
        additionalInfo->setReadOnly(true);
        break;

    case TA_DETAIL_TASK:
        listLabel->setText("Viewing your task:");
        saveButton->setEnabled(false);
        mainBody->setReadOnly(true);
        additionalInfo->setReadOnly(true);
        break;

    case TA_DETAIL_EVAL:
        listLabel->setText("Viewing your evaluation:");
        saveButton->setEnabled(false);
        mainBody->setReadOnly(true);
        additionalInfo->setReadOnly(true);
        break;
    }

}
void ViewIndividualDialog::handleCloseButton(){
    myParent->closeIndividualDialog(this);
    myParent->setSave(false);
}
void ViewIndividualDialog::handleSaveButton(){
    myParent->setSave(true);
    handleCloseButton();
}
void ViewIndividualDialog::updateInfo(std::string s1,std::string s2){
    additionalInfo->setText(QString(s1.c_str()));
    mainBody->setText(QString(s2.c_str()));
}

void ViewIndividualDialog::setType(viewIndividualType){}
viewIndividualType ViewIndividualDialog::getType(){
    return type;
}
std::string ViewIndividualDialog::getTitle(){
    return additionalInfo->text().toStdString();
}
std::string ViewIndividualDialog::getBody(){
    return mainBody->toPlainText().toStdString();
}
