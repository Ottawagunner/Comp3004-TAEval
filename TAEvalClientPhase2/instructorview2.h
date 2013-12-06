#ifndef TAEVALVIEW_H
#define TAEVALVIEW_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class TAEvalView;
}

class TAEvalView : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TAEvalView(QWidget *parent = 0);
    ~TAEvalView();
    
private:
    Ui::TAEvalView *ui;
    virtual void closeEvent(QCloseEvent *e);
};

#endif // TAEVALVIEW_H
