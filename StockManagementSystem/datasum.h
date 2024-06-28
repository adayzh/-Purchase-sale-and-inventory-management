#ifndef DATASUM_H
#define DATASUM_H

#include <QWidget>

namespace Ui {
class Datasum;
}

class Datasum : public QWidget
{
    Q_OBJECT

public:
    explicit Datasum(QWidget *parent = nullptr);
    ~Datasum();

signals:
    void refreshTableRequested();
private slots:
    void on_summary_clicked();

    void on_imputsum_clicked();

    void on_outputsum_clicked();

    void on_export_2_clicked();

    void InitTableWidget();

    void TableWidgetListData();

private:
    Ui::Datasum *ui;
};

#endif // DATASUM_H
