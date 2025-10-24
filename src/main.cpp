#include "qapplication.h"
#include "src/AppManager.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    AppManager manager;
    return a.exec();
}

