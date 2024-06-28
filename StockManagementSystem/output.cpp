#include "output.h"
#include "ui_output.h"

output::output(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::output)
{
    ui->setupUi(this);
    //禁止窗口最大化
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);

    //禁止拖动窗口大小
    setFixedSize(this->width(),this->height());

    //初始化ComboBox控件（读取数据库，获取编号）
    InitComboBoxFunc();
    connect(ui->outputpushButton, &QPushButton::clicked, this, &output::refreshTableRequested);

}

output::~output()
{
    delete ui;
}

void output::on_esc_clicked()
{
    this->close();
}

void output::on_outputpushButton_clicked()
{

    QString inputText = ui->amountlineEdit->text();
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


        int inputamount=ui->amountlineEdit->text().toInt();
        int tableamount=stockAmount.toInt();
        int sub=tableamount-inputamount;

        if(sub>=0&&inputamount>0){

        QSqlQuery sqlupdate;
        QString updatequery = QString("update commoditydatatable set StockAmount='%1' where StockId = '%2';").arg(sub).arg(selectedNumber);




        if (sqlupdate.exec(updatequery)) {
            QMessageBox::information(this,"Tips","库存更新成功！");
        }
        }
        else if(sub<0){
            QMessageBox::information(this,"Tips","出库失败，出库数量大于库存数量，请重新输入！");
        }

}
void output::InitComboBoxFunc()//初始化combo box控件
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
