#include "vdo_2.h"
#include "ui_vdo_2.h"
#include "dialog.h"
#include "vdo.h"
#include <QTabWidget>

/*This file contains the dat object generator for Discover SVID's,
 * Discover Modes, and the different modes
 */

union VDM_HEADER {

    unsigned int Val;

    struct {
        unsigned int data       : 15;
        unsigned int type       : 1;
        unsigned int svid       : 16;
    }unstruct;

    struct {
        unsigned int cmd        : 5;
        unsigned int reser2     : 1;
        unsigned int cmd_type   : 2;
        unsigned int obj_pos    : 3;
        unsigned int resrv1     : 2;
        unsigned int vdm_ver    : 2;
        unsigned int type       : 1;
        unsigned int svid       : 16;
    }structr;

    struct {
        unsigned int mode       : 32;
    }modes;

}vdms;

union SVID {
    unsigned int SVID;
    struct {
        unsigned int SVIDn      : 16;
    }flds;
}svid;

int n = 0, count1 = 0, count2 = 0;
QString header, objects;

VDO_2::VDO_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VDO_2)
{
    ui->setupUi(this);

    ui->comboBox_3->addItem("Unstructured VDM");
    ui->comboBox_3->addItem("Structured VDM");

    ui->comboBox->addItem("Initiator");
    ui->comboBox->addItem("Responder ACK");
    ui->comboBox->addItem("Responder NAK");
    ui->comboBox->addItem("Responder BUSY");

    ui->comboBox_2->addItem("Discover Identity");
    ui->comboBox_2->addItem("Discover SVIDs");
    ui->comboBox_2->addItem("Discover Modes");
    ui->comboBox_2->addItem("Enter Mode");
    ui->comboBox_2->addItem("Exit Mode");
    ui->comboBox_2->addItem("Attention");

    ui->lineEdit->setMaxLength(4);
    ui->lineEdit_2->setMaxLength(1);
    ui->lineEdit_6->setMaxLength(4);
}

void VDO_2::reset()
{
    ui->lineEdit_3->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_6->clear();
    header.clear();
    objects.clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
}

void VDO_2::on_pushButton_pressed()
{
    if(ui->comboBox_3->currentIndex() == 0) {
        vdms.unstruct.type = 0;
        vdms.unstruct.svid = ui->lineEdit->text().toUInt(&ok1, 16);
        vdms.unstruct.data = ui->lineEdit_6->text().toUInt(&ok1, 16);

        header.append(QString::number(vdms.Val,16));
        ui->lineEdit_7->setText(header);
    }

    else if(ui->comboBox_3->currentIndex() == 1) {
        vdms.structr.type = 1;
        vdms.structr.svid = ui->lineEdit->text().toUInt(&ok1, 16);
        vdms.structr.vdm_ver = 0;
        vdms.structr.resrv1 = 0;
        vdms.structr.obj_pos = ui->lineEdit_2->text().toUInt(&ok1, 16);
        vdms.structr.cmd_type = ui->comboBox->currentIndex();
        vdms.structr.reser2 = 0;
        vdms.structr.cmd = (ui->comboBox_2->currentIndex() + 1);

        header.append(QString::number(vdms.Val,16));
        ui->lineEdit_7->setText(header);
    }

    if(ui->comboBox->currentIndex() == 1)
    {
        if(ui->comboBox_2->currentIndex() == 0) {
            vdo->getText(header);
            /*here the VDM header generated in the VDO tab is
             * transferred to the next widget i.e., vdo ui using
             * the getText function.
             */
            vdo->show();
            /*If the command is of type Discover Identity,
             * then the widget is switched to the vdo ui
             * using the show() function
             */
        }

        else if(ui->comboBox_2->currentIndex() == 1) {
            QStringList str1 = ui->lineEdit_3->text().split(',');
            int x = str1.size();
            for(int i=0; i<x; i++)
                objects.append(str1[i]);

            /*The if-else block here is used to determine the
             * number of SVID's entered by the user as it is
             * required to append 0x0000 at the end of the data
             * object in different formats depending on odd or
             * even number of SVID's.
             */

            if( x%2 == 0) {
                for(int i=0;i<2;i++)
                    objects.append("0000");
            }
            else
                objects.append("0000");

            ui->lineEdit_8->setText(objects);
        }

        else if(ui->comboBox_2->currentIndex() == 2) {

            QStringList str1 = ui->lineEdit_5->text().split(',');
            int x = str1.size();
            for(int i=0; i<x; i++)
                objects.append(str1[i]);

            ui->lineEdit_8->setText(objects);
        }
    }
    reset();
    ui->lineEdit_9->setText("Done. Generated the required VDO");

}

VDO_2::~VDO_2()
{
    delete ui;
}


void VDO_2::on_pushButton_2_pressed()
{
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();
}
