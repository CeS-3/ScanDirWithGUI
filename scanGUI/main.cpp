#include "scanGUI.h"
#include <QtWidgets/QApplication>
#include"DirectoryNode.h"
#include"rootDir.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    scanGUI w;
    w.show();
    return a.exec();
}
