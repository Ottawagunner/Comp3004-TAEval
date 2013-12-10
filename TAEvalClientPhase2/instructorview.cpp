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
    setWindowTitle("Instructor");
}

InstructorView::~InstructorView(){
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
    ld = new ViewListDialog(this,INSTRUCT_VIEW_TASK);
    std::string additionalInfo =  ui->courseList->currentItem()->text().toStdString();
    control->reqViewAllTasks(additionalInfo);
    ld->show();
}
void InstructorView::on_viewTAButton_clicked(){
    ld = new ViewListDialog(this, INSTRUCT_VIEW_TA);
    std::string additionalInfo =  ui->courseList->currentItem()->text().toStdString();
    control->reqViewAllTAs(additionalInfo);
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
void InstructorView::listReq(viewIndividualType listReq, std::string title, std::string info){
    switch(listReq){
        case INSTRUCT_ADD_TASK:
            control->reqAddTask(title,info);
            break;
        case INSTRUCT_ADD_EVAL:
            control->reqAddEval(title,info);
            break;
        case INSTRUCT_DEL_TASK:
            control->reqDeleteTask(title);
            break;
        case INSTRUCT_DEL_EVAL:
            control->reqDeleteEval(title);
            break;
        case INSTRUCT_EDIT_TASK:
            control->reqEditTask(title, info);
            break;
        case INSTRUCT_EDIT_EVAL:
            control->reqEditEval(title,info);
            break;
        case INSTRUCT_DETAIL_TASK:
            control->reqViewTask(title);
            break;
        case INSTRUCT_DETAIL_EVAL:
            control->reqViewEval(title);
            break;
    }
}
void InstructorView::getListDialog(ViewListDialog** v){
    *v = ld;
}
void InstructorView::setSave(bool){}
void InstructorView::switchToTask(std::string s, ViewListDialog* v){
    closeListDialog(v);
    ld = new ViewListDialog(this,INSTRUCT_VIEW_TASK);
    control->reqViewAllTasks(s);
    ld->show();

}
