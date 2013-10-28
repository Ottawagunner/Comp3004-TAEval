#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "QAbstractButton"
#include "server.h"
#include "string"
#include "QDebug"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    Server host;

    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/TAEval/main.qml"));
    viewer.showExpanded();
    host.Setup();
    QString buffer = QString::fromStdString(host.ReciveText());
    qDebug()<<(buffer);

    return app->exec();
}
