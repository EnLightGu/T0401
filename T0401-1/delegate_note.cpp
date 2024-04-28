#include "delegate_note.h"
#include "item_note.h"

#include <QPainter>
// #include <QRectF>
// #include "WGlobal.h"

delegate_note::delegate_note() {}

void delegate_note::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.isValid()){
        int rowLineNum,rowHeight;//给rect分行,逐行安排内容
        QVariant var1 = index.data(Qt::UserRole);
        item_note item1 = var1.value<item_note>();//从model的standeditem中获取数据
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing);

        QRectF rect =  (option.rect);
        painter->drawRoundedRect(rect,20.0,80.0);
        painter->setPen(Qt::blue);
        // painter->setBrush(Qt::blue);
        painter->setFont(QFont("Microsoft YaHei",10));
        // painter->drawEllipse(10,10,rect.width(),rect.height());

        rowLineNum=3;
        rowHeight=rect.height()/rowLineNum;
        // painter->drawLine(rect.x(),rect.y(),rect.width(),rect.y());

        painter->drawLine(rect.x()+10,rect.y()+rowHeight,125,rect.y()+rowHeight);
        painter->drawText(QRectF(rect.x()+10,rect.y(),rect.width(),rowHeight),Qt::LeftToRight,item1.m_text);
        if(option.state.testFlag(QStyle::State_MouseOver))
        painter->drawText(QRectF(rect.x(),rect.y()+rowHeight,rect.width(),rowHeight*2),Qt::LeftToRight,item1.t_text);
        else;
        // painter->drawText(rect,Qt::AlignCenter,item1.t_text);
    }
}

QSize delegate_note::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // if(option.state.testFlag(QStyle::State_MouseOver))
        return QSize(option.rect.width(),60);//设置rectde大小
    // else
        // return QSize(option.rect.width(),20);
}

void delegate_note::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index)
{

}

void delegate_note::setModelData(QWidget *editor, const QAbstractItemModel *model, const QModelIndex &index)
{

}

void delegate_note::setEditorData(QWidget *editor, const QModelIndex &index)
{

}

QWidget *delegate_note::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index)
{

}
