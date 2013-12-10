#ifndef PREVENTENTER_H
#define PREVENTENTER_H
#include <QObject>
#include <QKeyEvent>
#include <QEvent>
class ViewIndividualDialog;

class PreventEnter : public QObject
{
    Q_OBJECT
public:
    //PreventEnter();
protected:
    bool eventFilter(QObject*, QEvent*);
};

#endif // PREVENTENTER_H
