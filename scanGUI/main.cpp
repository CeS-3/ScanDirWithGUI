﻿#include "scanGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    scanGUI w;
    w.show();
    return a.exec();
}
