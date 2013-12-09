#include "taview.h"
#include "ui_taview.h"

TAView::TAView(UIController *con, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TAView)
{
    ui->setupUi(this);
    control = con;
    setWindowTitle("TA");
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
{
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

void TAView::on_ViewEvalButton_clicked()
{
    id = new ViewIndividualDialog(this, TA_DETAIL_EVAL);
    control->reqViewEval(ui->taskList->currentItem()->text().toStdString());
    id->show();
}
void TAView::listReq(viewIndividualType, std::string){}
void TAView::getIndDialog(ViewIndividualDialog** v){
    *v = id;
}
void TAView::addToTaskList(std::string s){
    ui->taskList->addItem(QString(s.c_str()));
}
void TAView::setSave(bool){}
