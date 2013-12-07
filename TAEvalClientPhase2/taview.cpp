#include "taview.h"
#include "ui_taview.h"

TAView::TAView(UIController *con, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TAView)
{
    ui->setupUi(this);
    control = con;
}

TAView::~TAView()
{
    delete ui;
}

void TAView::on_logoutButton_clicked()
{
    control->logoutNotify();
}

void TAView::closeListDialog(ViewListDialog* ld){
    ld->hide();
    delete(ld);
}

void TAView::closeIndividualDialog(ViewIndividualDialog* id){
    id->hide();
    delete(id);
}

void TAView::on_ViewTaskButton_clicked()
{
    ViewListDialog *ld = new ViewListDialog(this, TA_VIEW_TASK);
    control->reqViewAllTasks("");
    ld->show();
}

void TAView::on_ViewEvalButton_clicked()
{
    ViewListDialog *ld = new ViewListDialog(this, TA_VIEW_EVALS);
    control->reqViewAllEvals();
    ld->show();
}
void TAView::listReq(viewIndividualType listReq, std::string info){
    switch(listReq){
        case TA_DETAIL_TASK:
            control->reqViewTask(info);
            break;
        case TA_DETAIL_EVAL:
            control->reqViewEval(info);
            break;

    }
}
