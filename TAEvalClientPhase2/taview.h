#ifndef TAVIEW_H
#define TAVIEW_H

#include <QMainWindow>
#include "uicontroller.h"
#include "viewtemplate.h"
#include "viewlistdialog.h"
#include "ViewIndividualDialog.h"
class ViewListDialog;
class ViewIndividualDialog;

namespace Ui {
class TAView;
}

class TAView : public QMainWindow, public viewTemplate
{
    Q_OBJECT
    
public:
    explicit TAView(UIController *con, QWidget *parent = 0);
    ~TAView();
    void closeListDialog(ViewListDialog*);
    void closeIndividualDialog(ViewIndividualDialog*);
    void listReq(viewIndividualType listReq, std::string);
    
private slots:
    void on_logoutButton_clicked();

    void on_ViewTaskButton_clicked();

    void on_ViewEvalButton_clicked();

private:
    Ui::TAView *ui;
    UIController* control;
};

#endif // TAVIEW_H
