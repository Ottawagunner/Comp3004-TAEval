#include "viewlistdialog.h"
#include <QtGui>
#include "types.h"

ViewListDialog::ViewListDialog(viewTemplate *viewParent, viewListType type, QWidget *parent)
{
    thisType = type;
    myParent = viewParent;
    listLabel = new QLabel("");
    add = new QPushButton("Add");
    edit = new QPushButton("Edit");
    del = new QPushButton("Delete");
    view = new QPushButton("Details");
    close = new QPushButton("Close");
    mylist = new QListWidget();

    switch(type){
        case INSTRUCT_VIEW_TASK:
            listLabel->setText("Viewing all tasks. Select a task and an option to modify the evaluation data");
            add->setText("Add Evaluation");
            break;

        case INSTRUCT_VIEW_TA:
            listLabel->setText("Viewing all TAs");
            break;

        case TA_VIEW_TASK:
            listLabel->setText("Viewing your tasks");
            add->setEnabled(false);
            del->setEnabled(false);
            edit->setEnabled(false);
            break;

        case TA_VIEW_EVALS:
            listLabel->setText("Viewing your evaluations");
            add->setEnabled(false);
            del->setEnabled(false);
            edit->setEnabled(false);
            break;

        default:
            listLabel->setText("THERE WAS AN ERROR");
            add->setEnabled(false);
            del->setEnabled(false);
            edit->setEnabled(false);
            view->setEnabled(false);
    }

    connect(add,SIGNAL(clicked()),this,SLOT(handleAddButton()));
    connect(edit,SIGNAL(clicked()),this,SLOT(handleEditButton()));
    connect(del,SIGNAL(clicked()),this,SLOT(handleDeleteButton()));
    connect(view,SIGNAL(clicked()),this,SLOT(handleViewButton()));
    connect(close,SIGNAL(clicked()),this,SLOT(handleCloseButton()));

    QVBoxLayout *left = new QVBoxLayout;
    left->addWidget(listLabel);
    left->addWidget(mylist);
    QVBoxLayout *right = new QVBoxLayout;
    right->addWidget(add);
    right->addWidget(edit);
    right->addWidget(del);
    right->addWidget(view);
    right->addWidget(close);
    QHBoxLayout *main = new QHBoxLayout;
    main->addLayout(left);
    main->addLayout(right);
    setLayout(main);

    setWindowTitle("View");

}
void ViewListDialog::handleAddButton(){
    ViewIndividualDialog *view;
    if(thisType == INSTRUCT_VIEW_TA){
        view = new ViewIndividualDialog(this,INSTRUCT_ADD_TASK);
        myParent->listReq(INSTRUCT_ADD_TASK);
    }
    else{
        view = new ViewIndividualDialog(this,INSTRUCT_ADD_EVAL);
        myParent->listReq(INSTRUCT_ADD_EVAL);
    }
    view->show();
}

void ViewListDialog::handleEditButton(){
    ViewIndividualDialog *view;
    if(thisType == INSTRUCT_VIEW_TA){
        view = new ViewIndividualDialog(this,INSTRUCT_EDIT_TASK);
        myParent->listReq(INSTRUCT_EDIT_TASK);
    }
    else{
        view = new ViewIndividualDialog(this,INSTRUCT_EDIT_EVAL);
        myParent->listReq(INSTRUCT_EDIT_EVAL);
    }
    view->show();
}

void ViewListDialog::handleDeleteButton(){
    if(thisType==INSTRUCT_VIEW_TA)
        myParent->listReq(INSTRUCT_DEL_TASK);
    if(thisType == INSTRUCT_VIEW_TASK)
        myParent->listReq(INSTRUCT_DEL_EVAL);
}

void ViewListDialog::handleViewButton(){
    ViewIndividualDialog *view;
    if(thisType == INSTRUCT_VIEW_TASK){
        view = new ViewIndividualDialog(this,INSTRUCT_DETAIL_EVAL);
        myParent->listReq(INSTRUCT_DETAIL_EVAL);
    }
    else if(thisType== INSTRUCT_VIEW_TA){
        view = new ViewIndividualDialog(this,INSTRUCT_DETAIL_TASK);
        myParent->listReq(INSTRUCT_DETAIL_TASK);
    }
    else if(thisType == TA_VIEW_TASK){
        view = new ViewIndividualDialog(this,TA_DETAIL_TASK);
        myParent->listReq(TA_DETAIL_TASK);
    }
    else if(thisType == TA_VIEW_EVALS){
        view = new ViewIndividualDialog(this,TA_DETAIL_EVAL);
        myParent->listReq(TA_DETAIL_EVAL);
    }
    view->show();
}

void ViewListDialog::handleCloseButton(){
    myParent->closeListDialog(this);
}

void ViewListDialog::closeListDialog(ViewListDialog*){}

void ViewListDialog::closeIndividualDialog(ViewIndividualDialog* id){
    id->hide();
    delete(id);
}
void ViewListDialog::listReq(viewIndividualType listReq){}
