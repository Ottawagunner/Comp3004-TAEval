#ifndef VIEWINDIVIDUALDIALOG_H
#define VIEWINDIVIDUALDIALOG_H
#include <QDialog>
#include "types.h"
#include "viewtemplate.h"

class QLabel;
class QPushButton;
class QLineEdit;
class QTextEdit;
class viewTemplate;

class ViewIndividualDialog:public QDialog
{
    Q_OBJECT

public:
    ViewIndividualDialog(viewTemplate* viewParent,enum viewIndividualType, QWidget *parent=0);
    void updateInfo(std::string,std::string);
    void setType(viewIndividualType t);

private slots:
    void handleCloseButton();
    void handleSaveButton();

private:
    viewTemplate* myParent;
    QLabel *listLabel;
    QPushButton *closeButton;
    QPushButton *saveButton;
    QLineEdit *additionalInfo;
    QTextEdit *mainBody;
    viewIndividualType type;
};

#endif // VIEWINDIVIDUALDIALOG_H
