#include "delegate_note.h"
#include "item_note.h"
#include "widget.h"

#include <QPainter>
// #include <QRectF>
// #include "WGlobal.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

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
        painter->drawRoundedRect(rect,15.0,20.0);//矩形的圆角
        if(option.state.testFlag(QStyle::State_Selected)){//颜色//选中
            painter->setPen(QPen(Qt::red));
            // painter->setBrush(Qt::darkBlue);
        }else{
            painter->setPen(QPen(Qt::darkGray));
            // painter->setBrush(QColor(229,241,255));
        }

        painter->setFont(QFont("Microsoft YaHei",10));
        // painter->drawEllipse(10,10,rect.width(),rect.height());

        rowLineNum=5;
        rowHeight=rect.height()/rowLineNum;

        // painter->drawLine(rect.x()+10,rect.y()+rowHeight,125,rect.y()+rowHeight);//划横线
        painter->drawLine(rect.x()+80,rect.y()+10,rect.x()+80,rect.y()+rowHeight*(rowLineNum)-10);//划竖线

        painter->drawText(QRectF(rect.x()+20,rect.y(),80-20,rect.height()),Qt::LeftToRight,item1.m_text);
        //选中
        // if(option.state.testFlag(QStyle::State_MouseOver) || option.state.testFlag(QStyle::State_Selected)){
            painter->drawText(QRectF(rect.x()+90,rect.y(),rect.width()-90-10,rect.height()),Qt::LeftToRight,item1.t_text);
        // }
        // else{
        //     };


        painter->restore();
        // painter->window();//??
    }
}

QSize delegate_note::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    QVariant v=index.data(Qt::UserRole);
    item_note i=v.value<item_note>();
    //设置rect的大小
    if(!option.state.testFlag(QStyle::State_Selected)){
        return QSize(option.rect.width(),40*2);
    }
    else{
        return QSize(option.rect.width(),120);
    }
        // if(i.isfold){
        //     return QSize(option.rect.width(),40);
        // }
        // else
        //     return QSize(option.rect.width(),120);
}

void delegate_note::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index)const
    // const override

{
    //编辑框
    int mouse_x = editor->mapFromGlobal(QCursor::pos()).x();
    int mouse_y = editor->mapFromGlobal(QCursor::pos()).y();

    QVariant v=index.data(Qt::UserRole);
    item_note i = v.value<item_note>();
    QRectF r=option.rect;
    int rownum,rowheight;
    rownum=5;
    rowheight=r.height()/rownum;
    // if(mouse_y<r.x()+r.width()/5-20){
    //     editor->setGeometry(r.x()+20,r.y()+3,80-20,r.height()-6);
    // }
    // else{
        editor->setGeometry(r.x()+1+80,r.y()+3,r.width()-80,r.height()-6);
    // }
    // return;

}

void delegate_note::setModelData(QWidget *editor,QAbstractItemModel *model, const QModelIndex &index)const
{
    //获取
    QTextEdit *text = static_cast<QTextEdit*>(editor);
    QString str=text->toPlainText();
    // QLineEdit *text = static_cast<QLineEdit*>(editor);
    // QString str=text->text();
    qDebug("str");
    //转存
    QVariant v=index.data(Qt::UserRole);
    item_note i = v.value<item_note>();
    i.t_text = str;
    v=QVariant::fromValue(i);
    // v.setValue<item_note>(i);
    //更新
    model->setData(index,v,Qt::UserRole);
    // int n = i.m_id;
    // Widget::fresh(n,v);
}

void delegate_note::setEditorData(QWidget *editor, const QModelIndex &index)const
{
    QString str="请输入:";
    QVariant v=index.data(Qt::UserRole);
    item_note i = v.value<item_note>();

    QTextEdit *text = static_cast<QTextEdit*>(editor);
    if(i.t_text==""){
        text->setText(str);}
    else {
        text->setText(i.t_text);
    }

}

QWidget *delegate_note::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index)const
{
    Q_UNUSED(option)
    if(!index.isValid()){
        return nullptr;
    }
    QTextEdit *editor = new QTextEdit(parent);
    return editor;
}
