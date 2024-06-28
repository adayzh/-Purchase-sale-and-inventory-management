#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

//操作数据库相关的头文件
#include<QSqlDatabase>
//sql查询
#include<QSqlQuery>
//sql报错
#include<QSqlError>
#include<QMessageBox>
#include<QtDebug>
#include<QTableWidgetItem>
#include<QStringList>
#include"add.h"
#include"in.h"
#include"output.h"
#include"datasum.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;


public:
    void ConnectMySQLDBFunc();//连接数据库

    void TableWidgetListData();//tablewidget表格控件初始化

    void InitTableWidget();//初始化列宽度

public slots:
    void refreshTableWidget();

private slots:
    void on_FindButton_clicked();
    void on_InButton_clicked();
    void on_OutButton_clicked();
    void on_AddButton_clicked();
    void on_DeleteButton_clicked();
    void on_ExportButton_clicked();
    void on_SummaryButton_clicked();

public:





};
#endif // MAINWIDGET_H
