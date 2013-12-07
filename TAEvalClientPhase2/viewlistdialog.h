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

    ViewListDialog(viewTemplate *viewParent, viewListType type,QWidget *parent=0);
    void closeListDialog(ViewListDialog*);
    void closeIndividualDialog(ViewIndividualDialog*);
    void listReq(viewIndividualType listReq, std::string);
private slots:
    void handleAddButton();
    void handleEditButton();
    void handleDeleteButton();
    void handleViewButton();
    void handleCloseButton();
private:
    viewListType thisType;
    QLabel *listLabel;
    QPushButton *add;
    QPushButton *edit;
    QPushButton *del;
    QPushButton *view;
    QPushButton *close;
    QListWidget *mylist;
    QList<QString> currList;
    viewTemplate* myParent;
};

#endif // VIEWLISTDIALOG_H
