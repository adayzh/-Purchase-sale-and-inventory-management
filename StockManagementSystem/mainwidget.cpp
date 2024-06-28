#include "mainwidget.h"
#include "ui_mainwidget.h"
#include"add.h"
#include"in.h"
#include"output.h"
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ConnectMySQLDBFunc();

    TableWidgetListData();

    InitTableWidget();


}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::ConnectMySQLDBFunc()//连接mysql数据库函数
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");//数据源ip
    db.setPort(3306);
    db.setDatabaseName("stockmsdb");//ODBC数据源名称
    db.setPassword("6512");//安装MySql数据库设置的密码

    bool bok=db.open();
    if(!bok){
         QMessageBox::information(this,"提示","数据库连接失败!");
    }
}
void MainWidget::TableWidgetListData()//tablewidget表格控件初始化
{
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setRowCount(200);


}

void MainWidget::on_FindButton_clicked()
{
    InitTableWidget();

    ui->tableWidget->clear();

    QSqlQuery sqlquery;
    QString strid="StockId=";
    strid=strid+ui->textEdit->text();

    QString str=QString("select * from commoditydatatable where %1").arg(strid);
    sqlquery.exec(str);

    // 设置表格控件标题（表头）
       ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"编号"<<"名称"<<"数量"<<"单价"<<"供应商家"<<"负责人"<<"入库时间"<<"出库时间"<<"备注");


    while (sqlquery.next()) {

        // 将数据库里面的数据表读取出来转换成对应的字符串,赋给对应字符串变量
        QString  strId=sqlquery.value(0).toString();
        QString  strName=sqlquery.value(1).toString();
        QString  strAmount=sqlquery.value(2).toString();
        QString  strPrice=sqlquery.value(3).toString();
        QString  strSup=sqlquery.value(4).toString();
        QString  strDir=sqlquery.value(5).toString();
        QString  strIntime=sqlquery.value(6).toString();
        QString  strOuttime=sqlquery.value(7).toString();
        QString  strRemarks=sqlquery.value(8).toString();


         // 将字符串显示到表格控件当中
        ui->tableWidget->setItem(0,0,new QTableWidgetItem(strId));
        ui->tableWidget->setItem(0,1,new QTableWidgetItem(strName));
        ui->tableWidget->setItem(0,2,new QTableWidgetItem(strAmount));
        ui->tableWidget->setItem(0,3,new QTableWidgetItem(strPrice));
        ui->tableWidget->setItem(0,4,new QTableWidgetItem(strSup));
        ui->tableWidget->setItem(0,5,new QTableWidgetItem(strDir));
        ui->tableWidget->setItem(0,6,new QTableWidgetItem(strIntime));
        ui->tableWidget->setItem(0,7,new QTableWidgetItem(strOuttime));
        ui->tableWidget->setItem(0,8,new QTableWidgetItem(strRemarks));

    }

}

void MainWidget::on_InButton_clicked()
{
    in *inlg=new in();
    inlg->show();
    connect(inlg, SIGNAL(refreshTableRequested()), this, SLOT(refreshTableWidget()));
}


void MainWidget::on_OutButton_clicked()
{
    output *outlg=new output();
    outlg->show();
    connect(outlg, SIGNAL(refreshTableRequested()), this, SLOT(refreshTableWidget()));
}

void MainWidget::on_AddButton_clicked()
{
        Add *add=new Add(); // 子窗口指针
add->show();
connect(add, SIGNAL(refreshTableRequested()), this, SLOT(refreshTableWidget()));
}

void MainWidget::on_DeleteButton_clicked()
{
    int iclick=QMessageBox::warning(this,"提示","删除操作是依据商品编号进行删除，是否继续？",QMessageBox::Yes|QMessageBox::No);

    // 2：判断用户是否单击Yes按钮
       if(iclick==QMessageBox::Yes)
       {
           // 3：获取当前选择行进行删除：商品记录数据
           int iRow=ui->tableWidget->currentRow();

           // 4：根据index（行，列）获取对应商品编号
           QString strValue=ui->tableWidget->model()->index(iRow,0).data().toString();
           // QMessageBox::information(this,"测试","获取数据为:"+strValue);

           QSqlQuery result;
           QString strid=strValue;

           // 5：判断删除商品编号是否为空？？？
           if(strid==NULL)
           {
               QMessageBox::critical(this,"错误","提示：请选择要删除商品编号，请重新检查？");
               return;
           }


           // 6：实现删除
           QString sqlquery=QString("delete from commoditydatatable where StockId = %1").arg(strid);
           if(result.exec(sqlquery))
           {
               // 删除提示
               QMessageBox::information(this,"提示","删除商品记录成功！");

               // 清空表格控件数据
               ui->tableWidget->clear();

               // 设置表格控件标题（表头）
               ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"编号"<<"名称"<<"数量"<<"单价"<<"供应商家"<<"负责人"<<"入库时间"<<"出库时间"<<"备注");

               // 调用函数将数据表中数据再次展示到表格控件当中
               InitTableWidget();
           }

       }
       else
       {
           return;
       }

}
// 导出数据
#include <QFileDialog>
#include <QAxObject>
#include <QDesktopServices>

void MainWidget::on_ExportButton_clicked()
{
    // 保存文件扩展名为：.xls
        QDateTime time;
        QString strTemp;

        // 1：获取当前系统当时作为文件名称进行保存
        time=QDateTime::currentDateTime();
        strTemp=time.toString("yyyy-MM-dd-hhmmss");
        // QMessageBox::information(this,"测试",strTemp);

        // 2：应用文件对话框来保存要导出文件名称(设置保存的文件名称)及数据信息
        QString strFileName=QFileDialog::getSaveFileName(this,tr("Excel Files"),QString("./%1%2.xls").arg(strTemp).arg("_kcgl"),tr("Excel Files(*.xls)"));
        // QMessageBox::information(this,"测试",strFileName);

        // 3：处理工作簿
        if(strFileName!=NULL)
        {
            QAxObject *excel=new QAxObject;
            if(excel->setControl("Excel.Application"));
            {
                excel->dynamicCall("SetVisible (bool Visible)",false);
                excel->setProperty("DisplayAlerts",false);

                QAxObject *workbooks=excel->querySubObject("WorkBooks"); // 获得工作簿集合
                workbooks->dynamicCall("Add"); // 创建一个工作簿
                QAxObject *workbook=excel->querySubObject("ActiveWorkBook"); // 获得当前工作簿
                QAxObject *worksheet=workbook->querySubObject("Worksheets(int)",1);
                QAxObject *cell;

                // 1：添加Excel文件表头数据
                for(int i=1;i<=ui->tableWidget->columnCount();i++)
                {
                    cell=worksheet->querySubObject("Cells(int,int)",1,i);
                    cell->setProperty("RowHeight",25);
                    cell->dynamicCall("SetValue(const QString&)",ui->tableWidget->horizontalHeaderItem(i-1)->data(0).toString());
                }

                // 2：将表格数据保存到Excel文件当中
                for(int j=2;j<=ui->tableWidget->rowCount()+1;j++)
                {
                    for(int k=1;k<=ui->tableWidget->columnCount();k++)
                    {
                        cell=worksheet->querySubObject("Cells(int,int)",j,k);
                        cell->dynamicCall("SetValue(const QString&",ui->tableWidget->item(j-2,k-1)->text()+"\t");

                    }
                }

                // 3：将刚才创建的Excel文件直接保存到指定的目录下
                workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(strFileName)); // 保存到strFileName
                workbook->dynamicCall("Close()");
                excel->dynamicCall("Quit()");
                delete excel;
                excel=NULL;
            }
        }


}

void MainWidget::on_SummaryButton_clicked()
{

}

void MainWidget::refreshTableWidget()
{
    InitTableWidget();
}

void MainWidget::InitTableWidget()//初始化列宽度
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
       ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"编号"<<"名称"<<"数量"<<"单价"<<"供应商家"<<"负责人"<<"入库时间"<<"出库时间"<<"备注");

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
