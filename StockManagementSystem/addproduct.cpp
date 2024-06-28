#include "addproduct.h"
#include "ui_add.h"
#include<QDateTime>
#include<QSqlQuery>

Add::Add(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);

    //禁止窗口最大化
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);

    //禁止拖动窗口大小
    setFixedSize(this->width(),this->height());
    connect(ui->Addcommodity, &QPushButton::clicked, this, &Add::refreshTableRequested);

}

Add::~Add()
{
    delete ui;
}

void Add::on_Esc_clicked()
{
    this->close();
}

void Add::on_Addcommodity_clicked()
{
    QSqlQuery sqlAdd;

    QString sid=ui->Addid->text();
    QString sname=ui->Addname->text();
    QString samount=ui->Addnumber->text();
    QString sprice=ui->Addprice->text();
    QString ssup=ui->Addsup->text();
    QString speo=ui->Addpeople->text();
    QString sremarks=ui->Addremarks->toPlainText();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString stime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");


    if(ui->Addid->text().isEmpty()){
        QMessageBox::critical(this,"提示！","新增商品编号不能为空，请重新输入！");
        ui->Addid->setFocus();
    }


    QString str=QString("INSERT INTO commoditydatatable(StockId, StockName, StockAmount,StockUnitPrice,Supplier,Director,WareHousTime,Remarks) VALUES ('%1','%2','%3','%4','%5','%6','%7','%8');")
            .arg(sid,sname,samount,sprice,ssup,speo,stime,sremarks);


    if(sqlAdd.exec(str)){
        QMessageBox::information(this,"Tips","恭喜你商品记录已插入");
    }
    else{
        QMessageBox::information(this,"Tips","商品记录插入失败");
    }

}
