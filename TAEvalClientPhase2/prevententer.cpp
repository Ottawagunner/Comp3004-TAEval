#include "prevententer.h"
bool PreventEnter::eventFilter(QObject *o, QEvent *e){
    if(e->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        if (keyEvent->key() == Qt::Key_Enter) {
            qDebug("HEY DONT DO THAT");
            return true;
        }
    }
    return QObject::eventFilter(o, e);
}
