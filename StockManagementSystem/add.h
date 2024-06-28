#ifndef ADD_H
#define ADD_H

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

namespace Ui {
class Add;
}

class Add : public QWidget
{
    Q_OBJECT

public:
    explicit Add(QWidget *parent = nullptr);
    ~Add();
signals:
    void refreshTableRequested();
private slots:
    void on_Esc_clicked();

    void on_Addcommodity_clicked();


private:
    Ui::Add *ui;
};

#endif // ADD_H
