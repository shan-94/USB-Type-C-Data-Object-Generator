#include "vdo.h"
#include "ui_vdo.h"

/*This file contains the functionality to generate
 * discover indentity data objects.
 */

union ID_HEADER_VDO {
    unsigned int Val;
    struct {
        unsigned int vendor_id  : 16;
        unsigned int resrv      : 10;
        unsigned int mod_sup    : 1;
        unsigned int prd_type   : 3;
        unsigned usb_dev        : 1;
        unsigned usb_host       : 1;
    }flds;
}id_vdo;

union CS_VDO {
    unsigned int Val;
    struct {
        unsigned int xid : 32;
    }flds;
}cs_vdo;

union PRODUCT_VDO {
    unsigned int Val;
    struct {
        unsigned int bcd_dev    : 16;
        unsigned int pd_id      : 16;
    }flds;
}product_vdo;

union PASSIVE_VDO {

    unsigned int Val;

    struct {
        unsigned int sup_speed       : 4;
        unsigned int resrv_1         : 1;
        unsigned int Vb_cab          : 1;
        unsigned int cur_cap         : 2;
        unsigned int SSRX2           : 1;
        unsigned int SSRX1           : 1;
        unsigned int SSTX2           : 1;
        unsigned int SSTX1           : 1;
        unsigned int cab_term_type   : 2;
        unsigned int cab_lat         : 4;
        unsigned int resrv_2         : 1;
        unsigned int usb_type        : 2;
        unsigned int resrv_3         : 4;
        unsigned int fw_ver          : 4;
        unsigned int hw_ver          : 4;
    }flds;
}pass_vdo;

union ACTIVE_VDO {

    unsigned int Val;

    struct {
        unsigned int sup_speed       : 3;
        unsigned int SOP_cont        : 1;
        unsigned int Vb_cab          : 1;
        unsigned int cur_cap         : 2;
        unsigned int SSRX2           : 1;
        unsigned int SSRX1           : 1;
        unsigned int SSTX2           : 1;
        unsigned int SSTX1           : 1;
        unsigned int cab_term_type   : 2;
        unsigned int cab_lat         : 4;
        unsigned int resrv_2         : 1;
        unsigned int usb_type        : 2;
        unsigned int resrv_3         : 4;
        unsigned int fw_ver          : 4;
        unsigned int hw_ver          : 4;
    }flds;
}act_vdo;

union ALTMODE_VDO {

    unsigned int Val;

    struct {
        unsigned int sup_speed       : 3;
        unsigned int Vbus_req        : 1;
        unsigned int Vcon_req        : 1;
        unsigned int Vcon_pwr        : 3;
        unsigned int SSRX2           : 1;
        unsigned int SSRX1           : 1;
        unsigned int SSTX2           : 1;
        unsigned int SSTX1           : 1;
        unsigned int resrv           : 12;
        unsigned int fw_ver          : 4;
        unsigned int hw_ver          : 4;
    }flds;
}altmode_vdo;

int num1 = 0,ctr1 = 0;
QString display1, data_objs;
QChar ch1 = ',';

VDO::VDO(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VDO)
{
    ui->setupUi(this);

    ui->comboBox_2->addItem("PDUSB Hub");
    ui->comboBox_2->addItem("PDUSB Peripheral");
    ui->comboBox_2->addItem("Passive Cable");
    ui->comboBox_2->addItem("Active Cable");
    ui->comboBox_2->addItem("Alt Mode Adapter");

    ui->cert->setMaxLength(8);
    ui->pd_id->setMaxLength(4);
    ui->bdc_dev->setMaxLength(4);
    ui->hw_ver->setMaxLength(2);
    ui->fw_ver->setMaxLength(2);
    ui->usb_type->setMaxLength(2);
    ui->cab_lat->setMaxLength(2);
    ui->cab_term->setMaxLength(2);
    ui->cur_cap->setMaxLength(2);
    ui->sup_speed->setMaxLength(2);
    ui->vcon_pwr->setMaxLength(2);
    ui->spinBox->setMaximum(3);
    ui->lineEdit->setMaxLength(4);
}

VDO::~VDO()
{
    delete ui;
}

void VDO::reset()
{
    ui->hw_ver->clear();
    ui->fw_ver->clear();
    ui->usb_type->clear();
    ui->cab_lat->clear();
    ui->cab_term->clear();
    ui->cur_cap->clear();
    ui->sup_speed->clear();
    ui->vcon_pwr->clear();
    ui->checkBox_4->setChecked(false);
    ui->checkBox_5->setChecked(false);
    ui->checkBox_6->setChecked(false);
    ui->checkBox_7->setChecked(false);
    ui->checkBox_8->setChecked(false);
    ui->checkBox_9->setChecked(false);
    ui->checkBox_19->setChecked(false);
    ui->checkBox_20->setChecked(false);
    display1.clear();
}


void VDO::reset_2()
{
    ui->spinBox->setValue(0);
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit->clear();
    ui->cert->clear();
    ui->pd_id->clear();
    ui->bdc_dev->clear();
}

void VDO::on_pushButton_clicked()
{
    /*ID HEADER VDO INITIALISATION*/
    id_vdo.flds.resrv = 0;
    id_vdo.flds.mod_sup = ui->checkBox_3->isChecked();
    id_vdo.flds.prd_type = ui->comboBox_2->currentIndex();
    id_vdo.flds.usb_dev = ui->checkBox_2->isChecked();
    id_vdo.flds.usb_host = ui->checkBox->isChecked();
    id_vdo.flds.vendor_id = ui->lineEdit->text().toUInt(&ok, 16);//check this
    display1.append(QString::number(id_vdo.Val,16));
    display1.append(ch1);

    /*CEST VDO INITIALISATION*/
    cs_vdo.flds.xid = ui->cert->text().toUInt(&ok,16);
    display1.append(QString::number(cs_vdo.Val,16));
    display1.append(ch1);

    /*PRODUCT VDO INITIALISATION*/
    product_vdo.flds.pd_id = ui->pd_id->text().toUInt(&ok ,16);
    product_vdo.flds.bcd_dev = ui->bdc_dev->text().toUInt(&ok, 16);
    display1.append(QString::number(product_vdo.Val,16));

    ui->output->setText(display1);

    /*PASSIVE VDO INITIALISATION*/
    if (ui->comboBox_2->currentIndex() == 2) {
        pass_vdo.flds.hw_ver = ui->hw_ver->text().toUInt(&ok,16);
        pass_vdo.flds.fw_ver = ui->fw_ver->text().toUInt(&ok, 16);
        pass_vdo.flds.resrv_3 = 0;
        pass_vdo.flds.usb_type = ui->usb_type->text().toUInt(&ok,16);
        pass_vdo.flds.resrv_2 = 0;
        pass_vdo.flds.cab_lat = ui->cab_lat->text().toUInt(&ok,16);
        pass_vdo.flds.cab_term_type = ui->cab_term->text().toUInt(&ok,16);
        pass_vdo.flds.SSTX1 = ui->checkBox_4->isChecked();
        pass_vdo.flds.SSTX2 = ui->checkBox_5->isChecked();
        pass_vdo.flds.SSRX1 = ui->checkBox_6->isChecked();
        pass_vdo.flds.SSRX2 = ui->checkBox_7->isChecked();
        pass_vdo.flds.cur_cap = ui->cur_cap->text().toUInt(&ok,16);
        pass_vdo.flds.Vb_cab = ui->checkBox_8->isChecked();
        pass_vdo.flds.resrv_1 = 0;
        pass_vdo.flds.sup_speed = ui->sup_speed->text().toUInt(&ok, 16);

        data_objs.append(QString::number(pass_vdo.Val,16));
        data_objs.append(ch1);
        num1++;
    }

    /*ACTIVE VDO INITIALISATION*/
    else if(ui->comboBox_2->currentIndex() == 3) {
        act_vdo.flds.hw_ver = ui->hw_ver->text().toUInt(&ok, 16);
        act_vdo.flds.fw_ver = ui->fw_ver->text().toUInt(&ok ,16);
        act_vdo.flds.resrv_3 = 0;
        act_vdo.flds.usb_type = ui->usb_type->text().toUInt(&ok ,16);
        act_vdo.flds.resrv_2 = 0;
        act_vdo.flds.cab_lat = ui->cab_lat->text().toUInt(&ok ,16);
        act_vdo.flds.cab_term_type = ui->cab_term->text().toUInt(&ok ,16);
        act_vdo.flds.SSTX1 = ui->checkBox_4->isChecked();
        act_vdo.flds.SSTX2 = ui->checkBox_5->isChecked();
        act_vdo.flds.SSRX1 = ui->checkBox_6->isChecked();
        act_vdo.flds.SSRX2 = ui->checkBox_7->isChecked();
        act_vdo.flds.cur_cap = ui->cur_cap->text().toUInt(&ok ,16);
        act_vdo.flds.Vb_cab = ui->checkBox_8->isChecked();
        act_vdo.flds.SOP_cont = ui->checkBox_9->isChecked();
        act_vdo.flds.sup_speed = ui->sup_speed->text().toUInt(&ok, 16);

        data_objs.append(QString::number(act_vdo.Val,16));
        data_objs.append(ch1);
        num1++;
    }

    /*ALT MODE VDO INITIALISATION*/
    else if(ui->comboBox_2->currentIndex() ==  4) {
        altmode_vdo.flds.hw_ver = ui->hw_ver->text().toUInt(&ok, 16);
        altmode_vdo.flds.fw_ver = ui->fw_ver->text().toUInt(&ok ,16);
        altmode_vdo.flds.resrv = 0;
        altmode_vdo.flds.SSTX1 = ui->checkBox_4->isChecked();
        altmode_vdo.flds.SSTX2 = ui->checkBox_5->isChecked();
        altmode_vdo.flds.SSRX1 = ui->checkBox_6->isChecked();
        altmode_vdo.flds.SSRX2 = ui->checkBox_7->isChecked();
        altmode_vdo.flds.Vcon_pwr = ui->vcon_pwr->text().toUInt(&ok, 16);
        altmode_vdo.flds.Vcon_req = ui->checkBox_19->isChecked();
        altmode_vdo.flds.Vbus_req = ui->checkBox_20->isChecked();
        altmode_vdo.flds.sup_speed = ui->sup_speed->text().toUInt(&ok ,16);

        data_objs.append(QString::number(altmode_vdo.Val,16));
        data_objs.append(ch1);
        num1++;
    }

    ui->lineEdit_9->setText(data_objs);
    ui->lineEdit_16->setText("Done. Enter the next VDO");
    reset();

    if(num1 == ctr1) {
        ui->lineEdit_16->setText("Generated all data objects");
        reset_2();
    }
}

void VDO::on_spinBox_valueChanged(int arg1)
{
    ctr1 = arg1;
}

void VDO::getText(QString txt)
{
    display1.append(txt);
    display1.append(ch1);
    ui->output->setText(display1);
}

void VDO::on_pushButton_2_pressed()
{
    ui->lineEdit_9->clear();
    ui->output->clear();
}
