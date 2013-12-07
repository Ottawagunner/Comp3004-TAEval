#ifndef INSTRUCTORVIEW_H
#define INSTRUCTORVIEW_H
#include <QMainWindow>
#include <QCloseEvent>
#include "clientcontrol.h"
#include "viewlistdialog.h"
#include "viewtemplate.h"
class UIController;

namespace Ui {
class InstructorView;
}

class InstructorView : public QMainWindow, public viewTemplate
{
    Q_OBJECT

public:
    explicit InstructorView(UIController *control, QWidget *parent=0);
    ~InstructorView();
    void addToList(std::string);
    void closeListDialog(ViewListDialog*);
    void closeIndividualDialog(ViewIndividualDialog*);
    void listReq(viewIndividualType listReq, std::string info);

private slots:
    void on_logoutButton_clicked();
    void on_viewTaskButton_clicked();
    void on_viewTAButton_clicked();

private:
    Ui::InstructorView *ui;
    virtual void closeEvent(QCloseEvent *e);
    UIController *control;
};

#endif
