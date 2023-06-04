
#include "mainwindow.h"
#define PROJECT_NAME "CodeAssistant"
#include <qtsingleapplication/src/QtSingleApplication>


int main(int argc, char *argv[])
{
    QtSingleApplication a(argc, argv);

    if (a.isRunning()) {
        if (a.arguments().size() > 1) {
            for(int i = 1; i < a.arguments().size(); i++) {
                a.sendMessage(a.arguments().at(i), 500);
            }
        }
        return 0;
    }
    QObject::connect(&a, &QtSingleApplication::messageReceived,[] {});
    a.setApplicationName(PROJECT_NAME);
    MainWindow w;
    w.show();
    return a.exec();
}
