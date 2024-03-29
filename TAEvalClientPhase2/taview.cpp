#include "taview.h"
#include "ui_taview.h"

TAView::TAView(UIController *con, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TAView)
{
    ui->setupUi(this);
    control = con;
    setWindowTitle("TA");
    ui->taskDetailsButton->setEnabled(false);
    ui->ViewEvalButton->setEnabled(false);
}

TAView::~TAView()
{
    delete ui;
}

void TAView::on_logoutButton_clicked()
{
    control->logoutNotify();
}

void TAView::closeListDialog(ViewListDialog*){}
void TAView::closeIndividualDialog(ViewIndividualDialog* ind){
    ind->hide();
}

void TAView::on_taskDetailsButton_clicked()
{   if(ui->taskList->currentItem() != NULL){
        id = new ViewIndividualDialog(this, TA_DETAIL_TASK);
        std::string input = ui->taskList->currentItem()->text().toStdString();
        if(!input.empty()){
            control->reqViewTask(ui->taskList->currentItem()->text().toStdString());
            id->show();
        }
        else{
            //GET ANGRY
        }
    }
}

void TAView::on_ViewEvalButton_clicked()
{
    if(ui->taskList->currentItem() != NULL){
        id = new ViewIndividualDialog(this, TA_DETAIL_EVAL);
        control->reqViewEval(ui->taskList->currentItem()->text().toStdString());
        id->show();
    }
}
void TAView::listReq(viewIndividualType, std::string, std::string, std::string){}
void TAView::getIndDialog(ViewIndividualDialog** v){
    *v = id;
}
void TAView::addToTaskList(std::string s){
    ui->taskList->addItem(QString(s.c_str()));
    ui->taskDetailsButton->setEnabled(true);
    ui->ViewEvalButton->setEnabled(true);

}
void TAView::setSave(bool){}
void TAView::switchToTask(std::string s, ViewListDialog* v, std::string){}
