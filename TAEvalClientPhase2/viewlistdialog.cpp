#include "viewlistdialog.h"
#include <QtGui>
#include "types.h"

ViewListDialog::ViewListDialog(viewTemplate *viewParent,viewListType type, QWidget *parent)
{
    save = false;
    thisType = type;
    myParent = viewParent;
    listLabel = new QLabel("");
    add = new QPushButton("Add");
    edit = new QPushButton("Edit");
    del = new QPushButton("Delete");
    view = new QPushButton("Details");
    close = new QPushButton("Close");
    mylist = new QListWidget();

    connect(add,SIGNAL(clicked()),this,SLOT(handleAddButton()));
    connect(edit,SIGNAL(clicked()),this,SLOT(handleEditButton()));
    connect(del,SIGNAL(clicked()),this,SLOT(handleDeleteButton()));
    connect(view,SIGNAL(clicked()),this,SLOT(handleViewButton()));
    connect(close,SIGNAL(clicked()),this,SLOT(handleCloseButton()));

    if(thisType == INSTRUCT_VIEW_TA){
        edit->setEnabled(false);
        del->setEnabled(false);
    }
    /*if(thisType == INSTRUCT_VIEW_TASK){
        del->setEnabled(false);
    }*/

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
    updateWindow();
}
void ViewListDialog::handleAddButton(){
    std::string currentCourse =  mylist->currentItem()->text().toStdString();
    if(thisType == INSTRUCT_VIEW_TA){
        viewID = new ViewIndividualDialog(this,INSTRUCT_ADD_TASK);
    }
    else{
        viewID = new ViewIndividualDialog(this,INSTRUCT_ADD_EVAL);
    }
    viewID->show();
}
void ViewListDialog::handleEditButton(){
    ViewIndividualDialog *view;
     std::string additionalInfo =  mylist->currentItem()->text().toStdString();
    if(thisType == INSTRUCT_VIEW_TA){
        viewID = new ViewIndividualDialog(this,INSTRUCT_EDIT_TASK);
        myParent->listReq(INSTRUCT_DETAIL_TASK, additionalInfo,"","");
    }
    else{
        viewID = new ViewIndividualDialog(this,INSTRUCT_EDIT_EVAL);
        myParent->listReq(INSTRUCT_DETAIL_EVAL, additionalInfo,"","");
    }
    viewID->show();
}
void ViewListDialog::handleDeleteButton(){
    std::string additionalInfo =  mylist->currentItem()->text().toStdString();
    if(thisType==INSTRUCT_VIEW_TA)
        myParent->listReq(INSTRUCT_DEL_TASK, additionalInfo,"","");
    if(thisType == INSTRUCT_VIEW_TASK)
        myParent->listReq(INSTRUCT_DEL_EVAL, additionalInfo,"","");
}
void ViewListDialog::handleViewButton(){
    std::string additionalInfo =  mylist->currentItem()->text().toStdString();
    if(thisType == INSTRUCT_VIEW_TASK){
        viewID = new ViewIndividualDialog(this,INSTRUCT_DETAIL_EVAL);
        myParent->listReq(INSTRUCT_DETAIL_EVAL, additionalInfo,"","");
        viewID->show();
    }
    else if(thisType== INSTRUCT_VIEW_TA){
        //viewID = new ViewIndividualDialog(this,INSTRUCT_DETAIL_TASK);
        //myParent->listReq(INSTRUCT_DETAIL_TASK, additionalInfo);
        myParent->switchToTask(additionalInfo, this);
    }
    else if(thisType == TA_VIEW_TASK){
        viewID = new ViewIndividualDialog(this,TA_DETAIL_TASK);
        myParent->listReq(TA_DETAIL_TASK,additionalInfo,"","");
        viewID->show();
    }
    else if(thisType == TA_VIEW_EVALS){
        viewID = new ViewIndividualDialog(this,TA_DETAIL_EVAL);
        myParent->listReq(TA_DETAIL_EVAL, additionalInfo,"","");
        viewID->show();
    }
}
void ViewListDialog::handleCloseButton(){
    myParent->closeListDialog(this);
}
void ViewListDialog::closeListDialog(ViewListDialog*){}
void ViewListDialog::closeIndividualDialog(ViewIndividualDialog* id){
    id->hide();
    if(save){
        viewIndividualType t = id->getType();
        myParent->listReq(t,id->getTitle(),id->getBody(),mylist->currentItem()->text().toStdString());
    }
    delete(id);
}
void ViewListDialog::listReq(viewIndividualType listReq, std::string title,std::string info, std::string listPiece){}
void ViewListDialog::updateList(std::string s){
    QString str(s.c_str());
    mylist->addItem(str);
}
void ViewListDialog::updateWindow(){
    switch(thisType){
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
}
void ViewListDialog::getIndivDialog(ViewIndividualDialog** d){
    *d = viewID;
}
void ViewListDialog::setSave(bool s){
    save = s;
}
void ViewListDialog::switchToTask(std::string s, ViewListDialog* v){

}
