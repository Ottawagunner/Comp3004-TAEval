#include "ViewIndividualDialog.h"
#include<QtGui>

ViewIndividualDialog::ViewIndividualDialog(viewTemplate *viewParent, viewIndividualType type, QWidget *parent)
{
    myParent = viewParent;

    listLabel = new QLabel("");
    closeButton = new QPushButton("Cancel");
    saveButton = new QPushButton("Save");
    additionalInfo = new QLineEdit;
    mainBody = new QTextEdit;

    connect(closeButton,SIGNAL(clicked()),this,SLOT(handleCloseButton()));
    connect(saveButton,SIGNAL(clicked()),this,SLOT(handleSaveButton()));

    QVBoxLayout *main = new QVBoxLayout;
    main->addWidget(listLabel);
    main->addWidget(additionalInfo);
    main->addWidget(mainBody);
    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addWidget(closeButton);
    buttons->addWidget(saveButton);
    main->addLayout(buttons);
    setLayout(main);

    switch(type){
    case INSTRUCT_ADD_TASK:
        listLabel->setText("Add new task:");
        break;

    case INSTRUCT_ADD_EVAL:
        listLabel->setText("Add new evaluation:");
        break;

    case INSTRUCT_DEL_TASK:
        listLabel->setText("Delete a task:");
        break;

    case INSTRUCT_DEL_EVAL:
        listLabel->setText("Delete an evaluation:");
        break;
    case INSTRUCT_EDIT_TASK:
        listLabel->setText("Edit a task:");
        break;

    case INSTRUCT_EDIT_EVAL:
        listLabel->setText("Edit an evaluation:");
        break;

    case INSTRUCT_DETAIL_TASK:
        listLabel->setText("Viewing a task:");
        break;

    case INSTRUCT_DETAIL_EVAL:
        listLabel->setText("Viewing an evaluation:");
        break;

    case TA_DETAIL_TASK:
        listLabel->setText("Viewing your task:");
        break;

    case TA_DETAIL_EVAL:
        listLabel->setText("Viewing your evaluation:");
        break;
    }

}
void ViewIndividualDialog::handleCloseButton(){
    myParent->closeIndividualDialog(this);
}
void ViewIndividualDialog::handleSaveButton(){
    qDebug("SAVE");
}
