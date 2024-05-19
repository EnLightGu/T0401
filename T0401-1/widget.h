#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QSqlDatabase>
#include <QSqlQuery>
#include "item_note.h" //
#include "delegate_note.h"
#include <QStringListModel> //
#include <QStandardItemModel>
#include <QModelIndex>

QT_BEGIN_NAMESPACE
namespace Ui {
class enlight;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void fresh(int n,QVariant v);

private slots:
    void on_pushButton_clicked();


    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();



private:
    Ui::enlight *ui;
    //
    //1 连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //2 数据库建表
    QSqlQuery q;
    //3 设置model view delegate
    QStandardItemModel *model_note;

    delegate_note *delegate;
    //4 数据定义
    QStandardItem *parentItem;

    struct item_note itemlist[1000];
        // = model_note->invisibleRootItem();
    // int rowcount;

    // const QModelIndex &parentI = QModelIndex() ;
    //数据读取
    //读取数据库拿出来,以便刷新
    void read();
    void write();
    void createtable();
    void connecttable();
    void insert();
};
#endif // WIDGET_H
