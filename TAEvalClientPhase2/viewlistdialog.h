#ifndef VIEWLISTDIALOG_H
#define VIEWLISTDIALOG_H
#include <QDialog>
#include "instructorview.h"
#include "ViewIndividualDialog.h"
//#include "viewtemplate.h"

class QLabel;
class QPushButton;
class QListWidget;
class InstructorView;
class viewTemplate;

class ViewListDialog :public QDialog, public viewTemplate
{
    Q_OBJECT
public:

    ViewListDialog(viewTemplate *viewParent, viewListType t,QWidget *parent=0);
    void closeListDialog(ViewListDialog*);
    void closeIndividualDialog(ViewIndividualDialog*);
    void listReq(viewIndividualType listReq,std::string,  std::string, std::string);
    void updateList(std::string);
    void updateWindow();
    void getIndivDialog(ViewIndividualDialog** d);
    void setSave(bool);
    void switchToTask(std::string s, ViewListDialog* v);
private slots:
    void handleAddButton();
    void handleEditButton();
    void handleDeleteButton();
    void handleViewButton();
    void handleCloseButton();
private:
    viewListType            thisType;
    QLabel*                 listLabel;
    QPushButton*            add;
    QPushButton*            edit;
    QPushButton*            del;
    QPushButton*            view;
    QPushButton*            close;
    QListWidget*            mylist;
    QList<QString>          currList;
    viewTemplate*           myParent;
    ViewIndividualDialog*   viewID;
    ViewListDialog*         taskList;
    bool                    save;
};

#endif // VIEWLISTDIALOG_H
