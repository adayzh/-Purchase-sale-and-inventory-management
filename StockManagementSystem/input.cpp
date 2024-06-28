#include "input.h"
#include "ui_in.h"
#include"mainwidget.h"

in::in(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::in)
{
    ui->setupUi(this);
    //禁止窗口最大化
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);

    //禁止拖动窗口大小
    setFixedSize(this->width(),this->height());

    //初始化ComboBox控件（读取数据库，获取编号）
    InitComboBoxFunc();
    connect(ui->inputpushButton, &QPushButton::clicked, this, &in::refreshTableRequested);


}
in::~in()
{
    delete ui;
}
void in::on_inputpushButton_clicked()
{


    QString inputText = ui->lineEdit->text();
        bool ok;
        double inputNumber = inputText.toDouble(&ok);

        if (!ok)  {
            QMessageBox::warning(this, "输入检查", "输入的不是数字,请重新输入");
        }




        QString selectedNumber=ui->comboBox_id->currentText();
        QSqlQuery sqlQuery;
        //获取指定编号商品的数量
        QString stockAmount;
        QString query = QString("SELECT * FROM commoditydatatable WHERE StockId = '%1';").arg(selectedNumber);

        if (sqlQuery.exec(query)) {
                if (sqlQuery.next()) {
                    stockAmount = sqlQuery.value(2).toString();

                } else {
                    QMessageBox::information(this, "库存量", "没有找到对应的库存量");
                }
            } else {
                qDebug() << "SQL 查询执行失败:" << sqlQuery.lastError();
                QMessageBox::critical(this, "SQL 错误", sqlQuery.lastError().text());
            }


        int inputamount=ui->lineEdit->text().toInt();
        int tableamount=stockAmount.toInt();
        int sum=inputamount+tableamount;

        if(sum>0){
        QSqlQuery sqlupdate;
        QString updatequery = QString("update commoditydatatable set StockAmount='%1' where StockId = '%2';").arg(sum).arg(selectedNumber);




        if (sqlupdate.exec(updatequery)) {
            QMessageBox::information(this,"Tips","库存更新成功！");
        }
}else {
            QMessageBox::information(this,"Tips","库存更新失败！");
        }



    }



void in::on_escpushButton_clicked()
{
     this->close();
}
void in::InitComboBoxFunc()//初始化combo box控件
{
    int i=0;
    QSqlQuery sqlQuery;
    sqlQuery.exec("SELECT StockId FROM commoditydatatable");


    QString StrId;

    while (sqlQuery.next()) {
        StrId=sqlQuery.value(0).toString();
        ui->comboBox_id->addItem(StrId);
      i++;
    }
}
