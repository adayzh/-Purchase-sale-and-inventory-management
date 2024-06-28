#include "datasum.h"
#include "ui_datasum.h"
#include<QDateTime>
//操作数据库相关的头文件
#include<QSqlDatabase>
//sql查询
#include<QSqlQuery>
//sql报错
#include<QSqlError>
#include<QMessageBox>
#include<QtDebug>

Datasum::Datasum(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Datasum)
{
    ui->setupUi(this);
    TableWidgetListData();

    InitTableWidget();


}

Datasum::~Datasum()
{
    delete ui;
}

void Datasum::on_summary_clicked()
{
    ui->tableWidget->setColumnWidth(0,80);
       ui->tableWidget->setColumnWidth(1,200);
       ui->tableWidget->setColumnWidth(2,80);
       ui->tableWidget->setColumnWidth(3,80);
       ui->tableWidget->setColumnWidth(4,100);

       ui->tableWidget->setColumnWidth(5,300);
       ui->tableWidget->setColumnWidth(6,80);
       ui->tableWidget->setColumnWidth(7,200);
       ui->tableWidget->setColumnWidth(8,200);
       ui->tableWidget->setColumnWidth(9,200);

       int i=0;
       QSqlQuery sqlquery;
       sqlquery.exec("select *from commoditydatatable");

       while(sqlquery.next())
       {
           QString StrId=sqlquery.value(0).toString();
           QString StrName=sqlquery.value(1).toString();
           QString StrAmount=sqlquery.value(2).toString();
           QString StrUnitPrice=sqlquery.value(3).toString();

           // 将商品数量 * 商品单价 = 商品总价
           double dSum=StrAmount.toDouble()*StrUnitPrice.toDouble();
           QString StrSum=QString("%1").arg(dSum);

           QString StrSupplier=sqlquery.value(4).toString();
           QString StrDirector=sqlquery.value(5).toString();
           QString StrWarehousingTime=sqlquery.value(6).toString();
           QString StrDeliveryTime=sqlquery.value(7).toString();
           QString StrRemarks=sqlquery.value(8).toString();

           ui->tableWidget->setItem(i,0,new QTableWidgetItem(StrId));
           ui->tableWidget->setItem(i,1,new QTableWidgetItem(StrName));
           ui->tableWidget->setItem(i,2,new QTableWidgetItem(StrAmount));
           ui->tableWidget->setItem(i,3,new QTableWidgetItem(StrUnitPrice));

           // 显示商品总价
           ui->tableWidget->setItem(i,4,new QTableWidgetItem(StrSum));

           ui->tableWidget->setItem(i,5,new QTableWidgetItem(StrSupplier));
           ui->tableWidget->setItem(i,6,new QTableWidgetItem(StrDirector));
           ui->tableWidget->setItem(i,7,new QTableWidgetItem(StrWarehousingTime));
           ui->tableWidget->setItem(i,8,new QTableWidgetItem(StrDeliveryTime));
           ui->tableWidget->setItem(i,9,new QTableWidgetItem(StrRemarks));

           i++;
}
}

void Datasum::on_imputsum_clicked()
{

}

void Datasum::on_outputsum_clicked()
{

}

void Datasum::on_export_2_clicked()
{

}

void Datasum::TableWidgetListData()//tablewidget表格控件初始化
{
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setRowCount(200);


}
void Datasum::InitTableWidget()//初始化列宽度
{
    QSqlQuery sqlquery;
    sqlquery.exec("select * from commoditydatatable");
    ui->tableWidget->setColumnWidth(0,60);
    ui->tableWidget->setColumnWidth(1,160);
    ui->tableWidget->setColumnWidth(2,60);
    ui->tableWidget->setColumnWidth(3,80);
    ui->tableWidget->setColumnWidth(4,160);
    ui->tableWidget->setColumnWidth(5,100);
    ui->tableWidget->setColumnWidth(6,200);
    ui->tableWidget->setColumnWidth(7,200);
    ui->tableWidget->setColumnWidth(8,160);

    // 设置表格控件标题（表头）
       ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"商品编号"<<"商品名称"<<"商品数量"<<"商品单价"<<"商品总价"<<"供应商家"<<"负责人"<<"入库时间"<<"出库时间"<<"备注");


    int i=0;
    while (sqlquery.next()) {
        QString  strId=sqlquery.value(0).toString();
        QString  strName=sqlquery.value(1).toString();
        QString  strAmount=sqlquery.value(2).toString();
        QString  strPrice=sqlquery.value(3).toString();
        QString  strSup=sqlquery.value(4).toString();
        QString  strDir=sqlquery.value(5).toString();
        QString  strIntime=sqlquery.value(6).toString();
        QString  strOuttime=sqlquery.value(7).toString();
        QString  strRemarks=sqlquery.value(8).toString();


        ui->tableWidget->setItem(i,0,new QTableWidgetItem(strId));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(strName));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(strAmount));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(strPrice));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(strSup));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(strDir));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(strIntime));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(strOuttime));
        ui->tableWidget->setItem(i,8,new QTableWidgetItem(strRemarks));

        i++;
    }
}
