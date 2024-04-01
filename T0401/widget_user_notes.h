#ifndef WIDGET_USER_NOTES_H
#define WIDGET_USER_NOTES_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget_user_notes;
}
QT_END_NAMESPACE

class Widget_user_notes : public QWidget
{
    Q_OBJECT

public:
    Widget_user_notes(QWidget *parent = nullptr);
    ~Widget_user_notes();

private:
    Ui::Widget_user_notes *ui;
};
#endif // WIDGET_USER_NOTES_H
