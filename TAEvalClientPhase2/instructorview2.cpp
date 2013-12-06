#include "instructorview.h"
#include "ui_taevalview.h"
#include <iostream>

TAEvalView::TAEvalView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TAEvalView)
{
    ui->setupUi(this);
}

TAEvalView::~TAEvalView()
{
    delete ui;
}
void TAEvalView::closeEvent(QCloseEvent *e){
        //std::cout<<"CLOSED"<<std::endl;
        //e->ignore();
}
