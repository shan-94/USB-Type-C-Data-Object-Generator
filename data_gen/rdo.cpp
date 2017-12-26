#include "rdo.h"
#include "ui_rdo.h"

union RDO
{
    unsigned int Val;

    struct
    {
        unsigned int min_cur            :  10;
        unsigned int op_cur             :  10;
        unsigned int rsrvd_1            :   4;
        unsigned int no_usb_suspend     :   1;
        unsigned int usb_comm           :   1;
        unsigned int cap_mismatch       :   1;
        unsigned int gvbk_flag          :   1;
        unsigned int obj_pos            :   3;
        unsigned int rsrvd_2            :   1;
    }fxd_var;

    struct
    {
        unsigned int max_op_pwr         :  10;
        unsigned int op_pwr             :  10;
        unsigned int rsrvd_1            :   4;
        unsigned int no_usb_suspend     :   1;
        unsigned int usb_comm           :   1;
        unsigned int cap_mismatch       :   1;
        unsigned int gvbk_flag          :   1;
        unsigned int obj_pos            :   3;
        unsigned int rsrvd_2            :   1;
    }bat;

}request_do;


rdo::rdo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rdo)
{
    ui->setupUi(this);

    ui->comboBox->addItem("Fixed & Variable Supply");
    ui->comboBox->addItem("Battery Supply");

    ui->op_curr->setMaximum(5.0);
    ui->min_curr->setMaximum(5.0);
    ui->op_pwr->setMaximum(100.0);
    ui->max_pwr->setMaximum(100.0);

}

rdo::~rdo()
{
    delete ui;
}

void rdo::reset()
{
    ui->comboBox->setCurrentIndex(0);
    ui->op_curr->setValue(0.0);
    ui->min_curr->setValue(0.0);
    ui->op_pwr->setValue(0);
    ui->max_pwr->setValue(0);
    ui->obj_pos_1->setValue(0);
    ui->opj_pos2->setValue(0);
    ui->sus_1->setChecked(false);
    ui->sus_2->setChecked(false);
    ui->cap_1->setChecked(false);
    ui->cap_2->setChecked(false);
    ui->gvk_1->setChecked(false);
    ui->gvk_2->setChecked(false);
    ui->coms_1->setChecked(false);
    ui->coms_2->setChecked(false);
}

void rdo::on_pushButton_clicked()
{
    if(ui->comboBox->currentIndex() == 0) {

        request_do.fxd_var.rsrvd_2 = 0;
        request_do.fxd_var.obj_pos = ui->obj_pos_1->value();
        request_do.fxd_var.gvbk_flag = ui->gvk_1->isChecked();
        request_do.fxd_var.cap_mismatch = ui->cap_1->isChecked();
        request_do.fxd_var.usb_comm = ui->coms_1->isChecked();
        request_do.fxd_var.no_usb_suspend = ui->sus_1->isChecked();
        request_do.fxd_var.rsrvd_1 = 0;

        double oc = ui->op_curr->value();
        request_do.fxd_var.op_cur = (oc * 1000)/10;

        double mc = ui->min_curr->value();
        request_do.fxd_var.min_cur = (mc * 1000)/10;

        QString val = QString::number(request_do.Val,16);

        ui->lineEdit->setText(val);
    }

    else if(ui->comboBox->currentIndex() == 1) {

        request_do.bat.rsrvd_2 = 0;
        request_do.bat.obj_pos = ui->opj_pos2->value();
        request_do.bat.gvbk_flag = ui->gvk_2->isChecked();
        request_do.bat.cap_mismatch = ui->cap_2->isChecked();
        request_do.bat.usb_comm = ui->coms_2->isChecked();
        request_do.bat.no_usb_suspend = ui->sus_2->isChecked();
        request_do.bat.rsrvd_1 = 0;

        double op = ui->op_pwr->value();
        request_do.bat.op_pwr = (op * 1000)/250;

        double mp = ui->max_pwr->value();
        request_do.bat.max_op_pwr = (mp * 1000)/250;

        QString val = QString::number(request_do.Val,16);

        ui->lineEdit->setText(val);

    }
    ui->lineEdit_10->setText("Data Object generated !");
    reset();
}

void rdo::on_pushButton_2_pressed()
{
    ui->lineEdit->clear();
    ui->lineEdit_10->clear();
}
