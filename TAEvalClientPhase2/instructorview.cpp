#include "instructorview.h"
#include "ui_instructorview.h"
#include "uicontroller.h"
#include <iostream>
#include "viewlistdialog.h"

InstructorView::InstructorView(UIController *con, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InstructorView)
{
    ui->setupUi(this);
    control = con;
    ui->welcomeLabel->setText("Welcome to the TAEval System");
}

InstructorView::~InstructorView()
{
    delete ui;
}
void InstructorView::closeEvent(QCloseEvent *e){
        //std::cout<<"CLOSED"<<std::endl;
        //e->ignore();
}
void InstructorView::addToList(std::string s){
    ui->courseList->addItem(QString(s.c_str()));
}

void InstructorView::on_logoutButton_clicked()
{
    control->logoutNotify();
}

void InstructorView::on_viewTaskButton_clicked()
{
    ViewListDialog *ld = new ViewListDialog(this,INSTRUCT_VIEW_TASK);
    //SEND REQUEST
    //UPDATE THE LIST
    //closeListDialog(ld);
    control->reqViewAllTasks();
    ld->show();
}
void InstructorView::on_viewTAButton_clicked(){
    ViewListDialog *ld = new ViewListDialog(this, INSTRUCT_VIEW_TA);
    control->reqViewAllTAs();
    ld->show();
}
void InstructorView::closeListDialog(ViewListDialog* temp){
    temp->hide();
    delete(temp);
}

void InstructorView::closeIndividualDialog(ViewIndividualDialog* temp){
    temp->hide();
    delete(temp);
}
void InstructorView::listReq(viewIndividualType listReq){
    switch(listReq){
        case INSTRUCT_ADD_TASK:
            control->reqAddTask();
            break;
        case INSTRUCT_ADD_EVAL:
            control->reqAddEval();
            break;
        case INSTRUCT_DEL_TASK:
            control->reqDeleteTask();
            break;
        case INSTRUCT_DEL_EVAL:
            control->reqDeleteEval();
            break;
        case INSTRUCT_EDIT_TASK:
            control->reqEditTask();
            break;
        case INSTRUCT_EDIT_EVAL:
            control->reqEditEval();
            break;
        case INSTRUCT_DETAIL_TASK:
            control->reqViewTask("");
            break;
        case INSTRUCT_DETAIL_EVAL:
            control->reqViewEval("");
            break;
    }
}
