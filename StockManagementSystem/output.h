#ifndef OUTPUT_H
#define OUTPUT_H

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
class output;
}

class output : public QWidget
{
    Q_OBJECT

public:
    explicit output(QWidget *parent = nullptr);
    ~output();
signals:
    void refreshTableRequested();

private slots:
    void on_esc_clicked();

    void on_outputpushButton_clicked();

private:
    Ui::output *ui;
public:
    void InitComboBoxFunc();//初始化combo box控件
};

#endif // OUTPUT_H
