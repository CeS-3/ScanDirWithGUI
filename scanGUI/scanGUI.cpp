#include "scanGUI.h"

scanGUI::scanGUI(QWidget *parent,std::string rootPath)
    : QMainWindow(parent),root(rootPath)
{
    //完成初始化
    ui.setupUi(this);
    //tab页 扫描统计
    connect(ui.startScanYes, SIGNAL(clicked()), this, SLOT(showstatic()));
    
    //tab页 统计文件信息
    connect(ui.staBrowsebtn, SIGNAL(clicked()), this, SLOT(onChoosePathButtonClicked1()));
    connect(ui.staYes,SIGNAL(clicked()),this,SLOT(showMystatResult()));
    
    //tab页 生成sql语句
    connect(ui.sqlPathBrowsebtn, SIGNAL(clicked()), this, SLOT(onChoosePathButtonClicked2()));
    connect(ui.sqlyes, SIGNAL(clicked()), this, SLOT(saveSqlFile()));
    
    //tab页 文件模拟操作
    connect(ui.browseBtn, SIGNAL(clicked()), this, SLOT(onChoosePathButtonClicked3()));
    connect(ui.dataFilePathYes, SIGNAL(clicked()), this, SLOT(showFilelist()));
    connect(ui.SelectYes, SIGNAL(clicked()), this, SLOT(excuteMyfile()));
    //tab页 目录模拟操作
    connect(ui.browseBtn2, SIGNAL(clicked()), this, SLOT(onChoosePathButtonClicked4()));
    connect(ui.dataFilePathYes2, SIGNAL(clicked()), this, SLOT(showDirlist()));
    connect(ui.SelectYes2, SIGNAL(clicked()), this, SLOT(excuteMydir()));

}

scanGUI::~scanGUI()
{}

//用于展示总体统计数据
void scanGUI::showstatic()
{
    //建树
    root.BuildTreeDFS();
    //动态生成行和列
    ui.DirSystemInfoTable->setRowCount(5); // 设置行数
    ui.DirSystemInfoTable->setColumnCount(1); // 设置列数

    // 添加表头
    ui.DirSystemInfoTable->setHorizontalHeaderLabels(QStringList() << "数据");
    ui.DirSystemInfoTable->setVerticalHeaderLabels(QStringList() << "子目录数量" << "文件总数量" << "目录层数" << "最长文件名" << "文件名长度");
    //根据root的统计信息进行输出
    QStringList dirSumList = { QString::number(root.GetDirSum()), QString::number(root.GetFileSum()), QString::number(root.GetDepth()), QString::fromStdString((root.GetMaxName())),QString::number(root.GetMaxNameLength())};

    // 设置第一列的内容
    for (int row = 0; row < 5; ++row) {
        //QTableWidgetItem对象在程序结束后会自动销毁，不会产生内存泄漏现象
        QTableWidgetItem* item = new QTableWidgetItem(dirSumList[row]);
        ui.DirSystemInfoTable->setItem(row, 0, item);
    }
    // 调整行列大小
    ui.DirSystemInfoTable->resizeRowsToContents();
    ui.DirSystemInfoTable->resizeColumnsToContents();
    QMessageBox::information(this, "提示", "扫描完成", QMessageBox::Ok);
}

//用于打开页面1的文件搜索界面
void scanGUI::onChoosePathButtonClicked1()
{
    QString directory = QFileDialog::getOpenFileName(this, "选择文件", QDir::homePath());
    if (!directory.isEmpty()) {
        // 处理选择的文件夹路径
        ui.staInputLine->setText(directory);
    }
}

//用于打开页面2的文件搜索界面
void scanGUI::onChoosePathButtonClicked2()
{
    QString directory = QFileDialog::getExistingDirectory(this, "选择文件夹", QDir::homePath());
    if (!directory.isEmpty()) {
        // 处理选择的文件夹路径
        ui.sqlPathInputLIine->setText(directory);
    }
}

//用于打开页面3的文件搜索界面
void scanGUI::onChoosePathButtonClicked3()
{
    QString directory = QFileDialog::getOpenFileName(this, "选择文件", QDir::homePath());
    if (!directory.isEmpty()) {
        // 处理选择的文件夹路径
        ui.simPathLine->setText(directory);
    }
}

//用于打开页面4的文件搜索界面
void scanGUI::onChoosePathButtonClicked4()
{
    QString directory = QFileDialog::getOpenFileName(this, "选择文件", QDir::homePath());
    if (!directory.isEmpty()) {
        // 处理选择的文件夹路径
        ui.simPathLine2->setText(directory);
    }
}

//使用一个计数器记录调用次数
//第一次调用根据数据文件mystat进行文件统计得到数据组first并填充入表格ui.staInfoTable中，若统计成功则使调用次数加1,并阻止对数据文件路径的修改
//按钮变为"再次统计"，第二次按下按钮则会对数据再次进行统计得到数据组second，并与first进行对比得出差异写入输出台中，
//第三次按下按钮则再次统计数据并得到third,经过对比得到差异进行输出，此时恢复输入数据文件路径的功能，计数器归零
void scanGUI::showMystatResult(){
    //三次调用都需要获取路径并检查文件格式
    //获取路径
    std::string targetFilePath = (ui.staInputLine->text()).toStdString();
    std::ifstream datafile(targetFilePath);
    if (!datafile.is_open()) {
        QMessageBox::critical(this, "错误", "该文件不存在！", QMessageBox::Ok);
        return;
    }
    //解析该文件
    std::string eachline;
    //读取数据文件中的第一行
    std::getline(datafile, eachline);
    if (eachline != "stat dirs")
    {
        //进行错误处理
        QMessageBox::critical(this, "错误", "该文件格式不匹配！", QMessageBox::Ok);
        return;
    }
    //如果是第一次调用该函数
    if (staTime == 0) {
        //先清空第一次统计的结果
        first.clear();
        mystatLine each(&root);
        //进行统计
        while (std::getline(datafile, eachline)) {
            if (eachline == "end of dirs")
                break;
            each.setLine(eachline);
            first.push_back(each.statisticalOperation());
        }
        //生成一个五列多行的表格
        ui.staInfoTable->setRowCount(first.size()); // 设置行数
        ui.staInfoTable->setColumnCount(5); // 设置列数
        //生成列头
        QStringList header;
        header << "目录" << "最早时间的文件" << "最晚时间的文件" << "文件总数" << "总的文件大小";
        ui.staInfoTable->setHorizontalHeaderLabels(header);
        // 设置表内容
        for (int row = 0; row < first.size(); row++) {
            DirInfo dirinfo = first[row];
            if (dirinfo.valid) {
                //设置该行内容
                QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(dirinfo.DirPath));
                ui.staInfoTable->setItem(row, 0, item);
                if (dirinfo.earliestFile.isValid()) {
                    item = new QTableWidgetItem(QString::fromStdString(dirinfo.earliestFile.GetName() + " " \
                        + std::to_string(dirinfo.earliestFile.GetSize()) + " bytes " + dirinfo.earliestFile.GetStandLastWriteTime()));
                    ui.staInfoTable->setItem(row, 1, item);
                }
                else {
                    item = new QTableWidgetItem(QString::fromStdString("无"));
                    ui.staInfoTable->setItem(row, 1, item);
                }
                if (dirinfo.latestFile.isValid()) {
                    item = new QTableWidgetItem(QString::fromStdString(dirinfo.latestFile.GetName() + " " \
                        + std::to_string(dirinfo.latestFile.GetSize()) + " bytes " + dirinfo.latestFile.GetStandLastWriteTime()));
                    ui.staInfoTable->setItem(row, 2, item);
                }
                else {
                    item = new QTableWidgetItem(QString::fromStdString("无"));
                    ui.staInfoTable->setItem(row, 2, item);
                }
                item = new QTableWidgetItem(QString::number(dirinfo.FileSum));
                ui.staInfoTable->setItem(row, 3, item);
                item = new QTableWidgetItem(QString::number(dirinfo.FileSumSize));
                ui.staInfoTable->setItem(row, 4, item);
            }
            else {
                QTableWidgetItem* baditem = new QTableWidgetItem(QString::fromStdString(dirinfo.DirPath + " 未找到"));
                ui.staInfoTable->setItem(row, 0, baditem);
                ui.staInfoTable->setItem(row, 1, nullptr);
                ui.staInfoTable->setItem(row, 2, nullptr);
                ui.staInfoTable->setItem(row, 3, nullptr);
                ui.staInfoTable->setItem(row, 4, nullptr);
            }

        }
        // 调整行列大小
        ui.staInfoTable->resizeRowsToContents();
        ui.staInfoTable->resizeColumnsToContents();
        QMessageBox::information(this, "提示", "统计完成", QMessageBox::Ok);
        //设置按钮上的文本为再次统计
        ui.staYes->setText("再次统计");
        //因为还要进行二次与三次统计所以需要阻止用户切换数据文件
        ui.staBrowsebtn->setEnabled(false);
        ui.staInputLine->setReadOnly(true);
        ui.staNo->setEnabled(false);
        //计数器加1
        staTime++;
    }
    //如果是第二次调用该函数
    else if (staTime == 1) {
        //先清空第二次统计的结果
        second.clear();
        mystatLine each(&root);
        //进行统计
        while (std::getline(datafile, eachline)) {
            if (eachline == "end of dirs")
                break;
            each.setLine(eachline);
            second.push_back(each.statisticalOperation());
        }
        //将第一次结果与第二次统计结果对比寻找差异
        std::string output;
        DirInfo::differ(first, second, output);
        //输出
        if (output != "")
            ui.DifferenceOutput->append(QString::fromStdString(output));
        else
            ui.DifferenceOutput->append(QString::fromStdString("无差异"));
        //计数器加1
        staTime++;
    }
    //若为第三次调用该函数
    else if (staTime == 2) {
        //先清空第三次统计的结果
        third.clear();
        mystatLine each(&root);
        //进行统计
        while (std::getline(datafile, eachline)) {
            if (eachline == "end of dirs")
                break;
            each.setLine(eachline);
            third.push_back(each.statisticalOperation());
        }
        //将第一次结果与第三次统计结果对比寻找差异
        std::string output;
        DirInfo::differ(first, third, output);
        //先清空第二次的输出
        ui.DifferenceOutput->clear();
        //输出
        if(output != "")
            ui.DifferenceOutput->append(QString::fromStdString(output));
        else
            ui.DifferenceOutput->append(QString::fromStdString("无差异"));
        //将计数器归0
        staTime = 0;
        //设置按钮上的文本为确定
        ui.staYes->setText("确定");
        //回复输入功能
        ui.staBrowsebtn->setEnabled(true);
        ui.staInputLine->setReadOnly(false);
        ui.staNo->setEnabled(true);
    }
}

//将生成的sql语句保存在指定目录下
void scanGUI::saveSqlFile() {
    //获取路径
    QString targetDir = ui.sqlPathInputLIine->text();
    //传入路径
    try {
        root.CreateSQL(targetDir.toStdString());
        QMessageBox::information(this, "提示", "保存完成", QMessageBox::Ok);
    }catch (const std::exception& e) {
        //如果不存在则报错
        QMessageBox::critical(this, "错误", "文件夹不存在！", QMessageBox::Ok);
    }
}

//在列表中显示myfile数据文件的每一条
void scanGUI::showFilelist() {
    //获取路径字符串
    QString text = ui.simPathLine->text();
    //开启文件
    std::ifstream datafile(text.toStdString());
    if (!datafile.is_open()) {
        //生成警告弹窗
        QMessageBox::critical(this, "错误", "文件不存在！", QMessageBox::Ok);
        return;
    }
    std::string eachline;
    //读取数据文件中的第一行
    std::getline(datafile, eachline);
    if (eachline != "selected files")
    {
        //进行错误处理
        QMessageBox::critical(this, "错误", "该文件格式不匹配！", QMessageBox::Ok);
        return;
    }
    //将原列表清空
    ui.DataFileList->clear();
    while (std::getline(datafile, eachline)) {
        if (eachline == "end of files")
            break;
        ui.DataFileList->addItem(QString::fromStdString(eachline));
    }
    //设置表项可多选
    ui.DataFileList->setSelectionMode(QAbstractItemView::MultiSelection);
}

//处理选中的myfile数据文件条目
void scanGUI::excuteMyfile() {
    // 获取被选中的项
    QList<QListWidgetItem*> selectedItems = ui.DataFileList->selectedItems();
    //处理选中的项
    myfileLine each(&root);
    for (QListWidgetItem* item : selectedItems) {
        //读取该行
        each.setLine(item->text().toStdString());
        //记录修改前后文件
        File before(true);
        File after(true);
        //执行相关操作
        each.excuteOperation(&before,&after);
        //展示差异
        std::string difference;
        difference += "文件路径: " + each.GetPath();
        
        //若两者均为合法，则M操作成功
        if (before.isValid() && after.isValid()) {
            difference += ("\n修改前:\n文件名:" + before.GetName() + ",文件大小:" + std::to_string(before.GetSize()) + " bytes,修改时间:" + before.GetStandLastWriteTime());
            difference += ("\n修改后:\n文件名:" + after.GetName() + ",文件大小:" + std::to_string(after.GetSize()) + " bytes,修改时间:" + after.GetStandLastWriteTime());
        }
        //before合法而after非法表示删除操作成功
        else if (before.isValid() && !after.isValid()) {
            difference += ("\n修改前:\n文件名:" + before.GetName() + ",文件大小:" + std::to_string(before.GetSize()) + " bytes,修改时间:" + before.GetStandLastWriteTime() + "\n修改后:\n文件不存在");
        }
        else if (!before.isValid() && after.isValid()) {
            difference += ("\n修改前:\n文件不存在\n修改后:\n文件名:" + after.GetName() + ",文件大小:" + std::to_string(after.GetSize()) + " bytes,修改时间:" + after.GetStandLastWriteTime());
        }
        else {
            difference += "\n修改失败";
        }
        ui.differenceOutput->addItem(QString::fromStdString(difference));
    }
}

//在列表中显示mydir数据文件的每一条
void scanGUI::showDirlist() {
    //获取路径字符串
    QString text = ui.simPathLine2->text();
    //开启文件
    std::ifstream datafile(text.toStdString());
    if (!datafile.is_open()) {
        //生成警告弹窗
        QMessageBox::critical(this, "错误", "文件不存在！", QMessageBox::Ok);
        return;
    }
    std::string eachline;
    //读取数据文件中的第一行
    std::getline(datafile, eachline);
    if (eachline != "selected dirs")
    {
        //进行错误处理
        QMessageBox::critical(this, "错误", "该文件格式不匹配！", QMessageBox::Ok);
        return;
    }
    //将原列表清空
    ui.DataFileList2->clear();
    while (std::getline(datafile, eachline)) {
        if (eachline == "end of dirs")
            break;
        ui.DataFileList2->addItem(QString::fromStdString(eachline));
    }
    //设置表项可多选
    ui.DataFileList2->setSelectionMode(QAbstractItemView::MultiSelection);
}

//处理选中的mydir数据文件条目
void scanGUI::excuteMydir() {
    ui.differenceOutput2->clear();
    // 获取被选中的项
    QList<QListWidgetItem*> selectedItems = ui.DataFileList2->selectedItems();
    ui.DataFileList2->clearSelection();
    //处理选中的项
    mydirLine each(&root);
    for (QListWidgetItem* item : selectedItems) {
        //读取该行
        each.setLine(item->text().toStdString());
        //进行操作
        std::vector<DirInfo> before;
        each.DeleteOperation(&before);
        //展示差异
        for (DirInfo eachInfo : before) {
            std::string difference;
            if (eachInfo.valid) {
                difference += "修改前:\n" + eachInfo.outPut();
                difference += "修改后:\n";
                difference += "目录不存在";
            }
            else {
                difference += "目录路径:" + item->text().toStdString() + "\n修改前:\n目录不存在\n修改后:\n目录不存在";
            }
            ui.differenceOutput2->addItem(QString::fromStdString(difference));
        }
    }

}