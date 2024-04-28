#include "widget.h"
#include "ui_widget.h"
#include "delegate_note.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //main

    //数据库 连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // db.setDatabaseName("../home/enlight/桌面/Qttest/T0401.1/T0401-1/notedb.db");
    db.setDatabaseName(":memory:");
    if(!db.open()){
        qDebug()<<"数据库打开失败!";
        return;
    }
    //数据库建表
    QSqlQuery q;
    QString createtable;
    createtable="create table notes(";
    createtable+="mid bigint primary key,";
    createtable+="mtext varchar(100),";
    createtable+="pid bigint,";
    createtable+="nid bigint,";
    createtable+="tid bigint,";
    createtable+="ttext varchar(1000)";
    createtable+=")";
    q.exec(createtable);
    // q.exec("create table notes(mid int primary key, mtext varchar(100))");
    // q.exec("INSERT INTO notes(mid,mtext)VALUES(1001,'mtext');");


            //换个QStandardItemModel用
    // view model delegate
    QStandardItemModel *model_note;
    model_note=new QStandardItemModel(this);
    delegate_note *delegate;
    QStandardItem *parentItem = model_note->invisibleRootItem();

    delegate = new delegate_note;
    ui->listView->setItemDelegate(delegate);
    ui->listView->setSpacing(3);
    ui->listView->setModel(model_note);
    ui->listView->setViewMode(QListView::ListMode);
    ui->listView->setDragEnabled(false);

    //数据定义 定义个item_note数组,在.h里,在这儿初始化?个,写到数据库里
    QString insert;
    for(int i=0;i<=100;i++){
        item_note *n1 = new item_note;
        n1->m_id = i;
        n1->m_text =
            "brief of num " + QString::number(i);
        n1->p_id = n1->m_id-1;
        n1->n_id = n1->m_id+1;
        n1->t_id = n1->m_id;
        n1->t_text =
            "whole text of " + QString::number(i);
        insert="INSERT INTO notes(mid,mtext,pid,nid,tid,ttext)VALUES(";
        insert=insert+ QString::number(n1->m_id) + ", ";
        insert=insert+ " ' " + n1->m_text + " ' , ";
        insert=insert+ QString::number(n1->p_id) + ", ";
        insert=insert+ QString::number(n1->n_id) + ", ";
        insert=insert+ QString::number(n1->t_id) + ", ";
        insert=insert+ " ' " + n1->t_text + " ' ";
        insert=insert+ ");";
        q.exec(insert);
    }
    //从数据库读取
    q.exec("SELECT * from notes");
    while(q.next()) {
        item_note *n2=new item_note;//只是个class或struct,存下数据的结构,作为中介.数据流:sql->item_note->qvariant->model->view
        n2->m_id=q.value(0).toInt();
        n2->m_text=q.value(1).toString();
        n2->p_id=q.value(2).toInt();
        n2->n_id=q.value(3).toInt();
        n2->t_id=q.value(4).toInt();
        n2->t_text=q.value(5).toString();
        QStandardItem *i1 = new QStandardItem;
        QVariant q1 = QVariant::fromValue(*n2);

        i1->setData(q1,Qt::UserRole);
        // i1->setData(n2->m_id,Qt::DisplayRole);
        i1->setData(n2->m_text,Qt::ToolTipRole);
        /*
        i1->setData(n1->m_id,Qt::UserRole);
        i1->setData(n1->m_text,Qt::UserRole+1);
        i1->setData(n1->m_text,Qt::DisplayRole);
        i1->setData(n1->p_id,Qt::UserRole+2);
        i1->setData(n1->n_id,Qt::UserRole+3);
        i1->setData(n1->t_id,Qt::UserRole+4);
        i1->setData(n1->t_text,Qt::UserRole+5);
*/
        parentItem->appendRow(i1);
    }



    //mainend
}

Widget::~Widget()
{
    delete ui;
}
