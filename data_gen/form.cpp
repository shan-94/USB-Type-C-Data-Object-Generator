#include "form.h"
#include "ui_form.h"
#include <QtWidgets>


form::form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::form)
{
    ui->setupUi(this);

}

form::~form()
{
    delete ui;
}
