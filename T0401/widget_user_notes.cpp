#include "widget_user_notes.h"
#include "ui_widget_user_notes.h"

Widget_user_notes::Widget_user_notes(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget_user_notes)
{
    ui->setupUi(this);
}

Widget_user_notes::~Widget_user_notes()
{
    delete ui;
}
