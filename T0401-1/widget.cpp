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
    , ui(new Ui::enlight)
{
    ui->setupUi(this);
    //main
//1 连接数据库
    connecttable();

//2 数据库建表
    createtable();

//3 设置view model delegate
    // QStandardItemModel *model_note;
    model_note=new QStandardItemModel(this);
    // &parent = QModelIndex();
    // delegate_note *delegate;
    // QStandardItem *parentItem = model_note->invisibleRootItem();
    parentItem = model_note->invisibleRootItem();

    delegate = new delegate_note;
    ui->listView->setItemDelegate(delegate);
    ui->listView->setSpacing(3);
    ui->listView->setModel(model_note);
    ui->listView->setViewMode(QListView::ListMode);
    ui->listView->setDragEnabled(false);


//4 数据定义 在这儿初始化?个,写到数据库里

//5 从数据库读取到自定义item->standeditem->model
    read();
    // write();
    read();

    // QModelIndexList selected = ui->listView->selectionModel()->selectedIndexes();



    //mainend
}

Widget::~Widget()
{
    delete ui;
}

void Widget::fresh(int n, QVariant v)
{
    v.setValue<item_note>(itemlist[n]);
}

void Widget::on_pushButton_clicked()
{
    write();
}

void Widget::read()
{
        //从数据库读取
        q.exec("SELECT * from notes");
        // rowcount=0;
        int i=0;
        parentItem->removeRows(0,parentItem->rowCount());
    while(q.next()) {
        // item_note *n2=new item_note;//只是个class或struct,存下数据的结构,作为中介.数据流:sql->item_note->qvariant->model->view
        i=q.value(0).toInt();
        itemlist[i].m_id=q.value(0).toInt();
        itemlist[i].m_text=q.value(1).toString();
        itemlist[i].p_id=q.value(2).toInt();
        itemlist[i].n_id=q.value(3).toInt();
        itemlist[i].t_id=q.value(4).toInt();
        itemlist[i].t_text=q.value(5).toString();
        itemlist[i].used = true;
        QStandardItem *i1 = new QStandardItem;
        QVariant v1 = QVariant::fromValue(itemlist[i]);

        i1->setData(v1,Qt::UserRole);
        i1->setData(itemlist[i].m_text,Qt::ToolTipRole);

        parentItem->appendRow(i1);

    }
}

void Widget::write()
{
    //怎么从index/item项中取出数据写到itemlist[]中?
    QVariant v_i;
    QModelIndex m;
    item_note item0;
    q.exec("DELETE from notes");
    QString ins;

    int i=0;
    while(i<parentItem->rowCount()){
        m = model_note->index(i,0,QModelIndex());
        v_i = m.data(Qt::UserRole);
        item0 = v_i.value<item_note>();
        ins="INSERT INTO notes(mid,mtext,pid,nid,tid,ttext)VALUES(";
        ins=ins+ QString::number(itemlist[item0.m_id].m_id) + ", ";
        ins=ins+ " '" + item0.m_text + "' , ";
        ins=ins+ QString::number(item0.p_id) + ", ";
        ins=ins+ QString::number(item0.n_id) + ", ";
        ins=ins+ QString::number(item0.t_id) + ", ";
        ins=ins+ " '" + item0.t_text + "' ";
        ins=ins+ ");";
        q.exec(ins);
        i++;
    }
    read();
}

void Widget::createtable()
{
    // QSqlQuery q;
    QString createtable;
    createtable="create table if not exists notes(";
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
}

void Widget::connecttable()
{
    // QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../T0401-1/notedb.db");
    // db.setDatabaseName(":memory:");
    if(!db.open()){
        qDebug()<<"数据库打开失败!";
        return;
    }
}

void Widget::insert()
{
    QString ins;
    // model_note->rowCount();

    int i=0;
    while(itemlist[i].used){i++;}
        itemlist[i].m_id = i;
        itemlist[i].m_text =
            "num" + QString::number(i);
        itemlist[i].p_id = itemlist[i].m_id-1;
        itemlist[i].n_id = itemlist[i].m_id+1;
        itemlist[i].t_id = itemlist[i].m_id;
        itemlist[i].t_text =
            "whole text of " + QString::number(i);
        ins="INSERT INTO notes(mid,mtext,pid,nid,tid,ttext)VALUES(";
        ins=ins+ QString::number(itemlist[i].m_id) + ", ";
        ins=ins+ " '" + itemlist[i].m_text + " ' , ";
        ins=ins+ QString::number(itemlist[i].p_id) + ", ";
        ins=ins+ QString::number(itemlist[i].n_id) + ", ";
        ins=ins+ QString::number(itemlist[i].t_id) + ", ";
        ins=ins+ " '" + itemlist[i].t_text + " ' ";
        ins=ins+ ");";
        q.exec(ins);

        read();

}



void Widget::on_pushButton_4_clicked()
{
    write();
    Widget::insert();
}


void Widget::on_pushButton_2_clicked()
{
    write();
    // read();
    //删除
    QModelIndex m = model_note->index(parentItem->rowCount()-1,0,QModelIndex());
    QVariant v_i = m.data(Qt::UserRole);
    item_note item0 = v_i.value<item_note>();
    QString ins;

    int i=item0.m_id;
    itemlist[i].used=false;
    ins="delete from notes where mid = ";
    ins=ins+ QString::number(i);
    ins=ins+ ";";
    q.exec(ins);
    read();

    // ui->listView->reset();
}







