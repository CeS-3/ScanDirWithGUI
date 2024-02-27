#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_scanGUI.h"
#include <QMessageBox>
#include<QFileDialog>
#include "rootDir.h"
#include"DirInfo.h"
#include"mydirLine.h"
#include"myfileLine.h"
#include"mystatLine.h"
class scanGUI : public QMainWindow
{
    Q_OBJECT

public:
    scanGUI(QWidget *parent = nullptr,std::string rootPath = "C:\\Windows");
    ~scanGUI();
private slots:
    void showFilelist();
    void showDirlist();
    void showstatic();
    void onChoosePathButtonClicked1();
    void onChoosePathButtonClicked2();
    void onChoosePathButtonClicked3();
    void onChoosePathButtonClicked4();
    void showMystatResult();
    void saveSqlFile();
    void excuteMyfile();
    void excuteMydir();
private:
    Ui::scanGUIClass ui;
    //目录树的根目录
    rootDir root;
    //记录统计次数的计数器
    int staTime = 0;
    //存储三次统计信息的向量
    std::vector<DirInfo> first;
    std::vector<DirInfo> second;
    std::vector<DirInfo> third;
    
};
