#ifndef DELEGATE_NOTE_H
#define DELEGATE_NOTE_H

#include <QStyledItemDelegate>

class delegate_note : public QStyledItemDelegate
{
public:
    delegate_note();
    void paint(QPainter *painter,const QStyleOptionViewItem &option,
                              const QModelIndex &index)const;
    QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index)const;
    //实现四个虚函数
    QWidget *createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index)const;
    void setEditorData(QWidget *editor,const QModelIndex &index)const;
    void setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index)const;
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index)const;
};

#endif // DELEGATE_NOTE_H
