#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_scanGUI.h"

class scanGUI : public QMainWindow
{
    Q_OBJECT

public:
    scanGUI(QWidget *parent = nullptr);
    ~scanGUI();

private:
    Ui::scanGUIClass ui;
};
