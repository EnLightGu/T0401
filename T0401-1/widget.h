#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "item_note.h" //
#include "delegate_note.h"
#include <QStringListModel> //
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    //
    // QVector<item_note> notes;
    //
    // QStringListModel *model;
    //
    // QStandardItemModel *model1;
    //
    delegate_note delegate;
};
#endif // WIDGET_H
