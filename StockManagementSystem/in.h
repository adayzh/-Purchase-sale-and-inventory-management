#ifndef IN_H
#define IN_H

#include <QWidget>
#include<QDateTime>
//操作数据库相关的头文件
#include<QSqlDatabase>
//sql查询
#include<QSqlQuery>
//sql报错
#include<QSqlError>
#include<QMessageBox>
#include<QtDebug>
#include "mainwidget.h"


namespace Ui {
class in;
}

class in : public QWidget
{
    Q_OBJECT

public:
    explicit in(QWidget *parent = nullptr);
    ~in();

signals:
    void refreshTableRequested();
private slots:
    void on_inputpushButton_clicked();

    void on_escpushButton_clicked();


private:
    Ui::in *ui;



public:
    void InitComboBoxFunc();//初始化combo box控件

};

#endif // IN_H
