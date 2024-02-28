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
    //用于展示myfile文件的条目
    void showFilelist();

    //用于展示mydir文件的条目
    void showDirlist();

    //用于展示统计结果
    void showstatic();
    
    //处理点击1号界面浏览目录按钮的弹窗响应
    void onChoosePathButtonClicked1();

    //处理点击2号界面浏览目录按钮时的弹窗响应
    void onChoosePathButtonClicked2();

    //处理点击3号界面浏览目录按钮时的弹窗响应
    void onChoosePathButtonClicked3();

    //处理点击4号界面浏览目录按钮时的弹窗响应
    void onChoosePathButtonClicked4();

    //处理mystat文件统计结果的展示
    void showMystatResult();

    //进行sql语句的保存
    void saveSqlFile();

    //执行选中的myfile条目
    void excuteMyfile();

    //执行选中的mydir条目
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
