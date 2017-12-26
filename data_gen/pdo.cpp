#include "pdo.h"
#include "ui_pdo.h"

/*Source Data Objects union struct
 * that contains fixed, battery
 * and variable dat objects structs
 */
union SRC_PDO
{
    unsigned int Val;

    struct  {
        unsigned int cur                :  10;
        unsigned int volt               :  10;
        unsigned int current_cap        :   2;
        unsigned int rsrvd              :   3;
        unsigned int dual_role          :   1;
        unsigned int usb_comm           :   1;
        unsigned int ex_powered         :   1;
        unsigned int usb_susp_sup       :   1;
        unsigned int dual_role_pwr      :   1;
        unsigned int sply_type          :   2;
    }fxd;

    struct  {
        unsigned int  max_current		:	10;
        unsigned int  min_voltage       :   10;
        unsigned int  max_voltage		:	10;
        unsigned int  supply_type       :   2;
    }var ;

    struct  {
        unsigned int  max_power		    :	10;
        unsigned int  min_voltage       :   10;
        unsigned int  max_voltage	    :	10;
        unsigned int  supply_type       :   2;
    }bat ;

}src_pdo;

/*Sink Data Objects union struct
 * that contains fixed, battery
 * and variable dat objects structs
 */
union SINK_PDO
{
    unsigned int Val;
    struct  {
        unsigned int cur                :  10;
        unsigned int volt               :  10;
        unsigned int rsrvd              :   5;
        unsigned int dual_role          :   1;
        unsigned int usb_comm           :   1;
        unsigned int ex_powered         :   1;
        unsigned int higher_cap         :   1;
        unsigned int dual_role_pwr      :   1;
        unsigned int supply_type        :   2;
    }fxd;

    struct  {
        unsigned int  op_current		:	10;
        unsigned int  min_voltage       :   10;
        unsigned int  max_voltage		:	10;
        unsigned int  supply_type       :   2;
    }var;

    struct  {
        unsigned int  op_power		    :	10;
        unsigned int  min_voltage       :   10;
        unsigned int  max_voltage	    :	10;
        unsigned int  supply_type       :   2;
    }bat;

}sink_pdo;

/*A union struct that is used to
 * determine the data object entered
 * by the user based on the supply type.
 */
union TYPE_DET
{
    unsigned int Val;
    struct {
        unsigned int reserved_1   : 10;
        unsigned int reserved_2   : 10;
        unsigned int reserved_3   : 10;
        unsigned int sply_type  : 2;
    }flds;
}type_det;

int num = 0,ctr = 0;
QString display;
QChar ch = ',';

PDO::PDO(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PDO)
{
    ui->setupUi(this);

    ui->pdo_type->addItem("Source");
    ui->pdo_type->addItem("Sink");

    ui->comboBox->addItem("Fixed Supply");
    ui->comboBox->addItem("Battery Supply");
    ui->comboBox->addItem("Variable Supply");

    ui->comboBox_2->addItem("0");
    ui->comboBox_2->addItem("1");
    ui->comboBox_2->addItem("2");
    ui->comboBox_2->addItem("3");

    ui->lineEdit_2->setMaxLength(8);
    ui->spinBox_2->setMaximum(7);
    ui->spinBox_2->setMinimum(0);
    //ui->doubleSpinBox_2->setMaximum(51200.0);
    ui->doubleSpinBox_2->setMaximum(5.00);
    ui->spinBox_8->setMaximum(5.00);
    ui->spinBox->setMaximum(20);
    ui->spinBox_7->setMaximum(20);
    ui->spinBox_6->setMaximum(20);
    ui->spinBox_4->setMaximum(20);
    ui->spinBox_3->setMaximum(20);
}

PDO::~PDO()
{
    delete ui;
}

/*The reset function is used to set all the various
 * widgets to default values to enable ease of use
 */
void PDO::reset()
{
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
    ui->checkBox_5->setChecked(false);
    ui->checkBox_6->setChecked(false);
    ui->spinBox->setValue(0);
    ui->doubleSpinBox_2->setValue(0.0);
    ui->spinBox_6->setValue(0);
    ui->spinBox_7->setValue(0);
    ui->spinBox_5->setValue(0.0);
    ui->spinBox_3->setValue(0);
    ui->spinBox_4->setValue(0);
    ui->spinBox_8->setValue(0.0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox->setCurrentIndex(0);
}

void PDO::on_pushButton_clicked()
{
    if(ui->pdo_type->currentIndex() == 0)
    {
        if(ui->comboBox->currentIndex() == 0)
        {
            src_pdo.fxd.sply_type = 0;
            src_pdo.fxd.dual_role = ui->checkBox_6->isChecked();
            src_pdo.fxd.dual_role_pwr = ui->checkBox->isChecked();
            src_pdo.fxd.ex_powered = ui->checkBox_2->isChecked();
            src_pdo.fxd.usb_susp_sup = ui->checkBox_3->isChecked();
            src_pdo.fxd.usb_comm = ui->checkBox_5->isChecked();
            src_pdo.fxd.rsrvd = 0;
            src_pdo.fxd.current_cap = ui->comboBox_2->currentIndex();

            int v = ui->spinBox->value();
            src_pdo.fxd.volt = (v * 1000)/50;
            /*multiplication by 1000 and division by 50 is to convert the value enetere
             * in 50mA units. This logic is used throughout the programs
             */

            double c = ui->doubleSpinBox_2->value();
            src_pdo.fxd.cur = (c * 1000)/10;

            display.append(QString::number(src_pdo.Val,16));
            ui->lineEdit->setText(display);
        }

        else if(ui->comboBox->currentIndex() == 1)
        {
            src_pdo.bat.supply_type = 1;

            int v_m = ui->spinBox_7->value();
            src_pdo.bat.max_voltage = (v_m * 1000)/50;

            v_m = ui->spinBox_6->value();
            src_pdo.bat.min_voltage = (v_m * 1000)/50;

            double c = ui->spinBox_5->value();

            src_pdo.bat.max_power = (c * 1000)/250;

            display.append(QString::number(src_pdo.Val,16));
            ui->lineEdit->setText(display);
        }

        else if(ui->comboBox->currentIndex() == 2)
        {
            src_pdo.var.supply_type = 2;

            int v_m = ui->spinBox_3->value();
            src_pdo.var.max_voltage = (v_m * 1000)/50;

            v_m = ui->spinBox_4->value();
            src_pdo.var.min_voltage = (v_m * 1000)/50;

            double c = ui->spinBox_8->value();
            src_pdo.var.max_current = (c * 1000)/10;

            display.append(QString::number(src_pdo.Val,16));
            ui->lineEdit->setText(display);
        }
    }
    else if(ui->pdo_type->currentIndex() == 1)
    {
        if(ui->comboBox->currentIndex() == 0)
        {
            sink_pdo.fxd.supply_type = 0;
            sink_pdo.fxd.dual_role = ui->checkBox_6->isChecked();
            sink_pdo.fxd.dual_role_pwr = ui->checkBox->isChecked();
            sink_pdo.fxd.ex_powered = ui->checkBox_2->isChecked();
            sink_pdo.fxd.higher_cap = ui->checkBox_4->isChecked();
            sink_pdo.fxd.usb_comm = ui->checkBox_5->isChecked();
            sink_pdo.fxd.rsrvd = 0;

            int v = ui->spinBox->value();
            sink_pdo.fxd.volt = (v * 1000)/50;

            double c = ui->doubleSpinBox_2->value();
            sink_pdo.fxd.cur = (c * 1000)/10;

            display.append(QString::number(sink_pdo.Val,16));
            ui->lineEdit->setText(display);
        }

        else if(ui->comboBox->currentIndex() == 1)
        {
            sink_pdo.bat.supply_type = 1;

            int v_m = ui->spinBox_7->value();
            sink_pdo.bat.max_voltage = (v_m * 1000)/50;

            v_m = ui->spinBox_6->value();
            sink_pdo.bat.min_voltage = (v_m * 1000)/50;

            double c = ui->spinBox_5->value();

            sink_pdo.bat.op_power = (c * 1000)/250;

            display.append(QString::number(sink_pdo.Val,16));
            ui->lineEdit->setText(display);
        }

        else if(ui->comboBox->currentIndex() == 2)
        {
            sink_pdo.var.supply_type = 2;

            int v_m = ui->spinBox_3->value();

            sink_pdo.var.max_voltage = (v_m * 1000)/50;
            v_m = ui->spinBox_4->value();
            sink_pdo.var.min_voltage = (v_m * 1000)/50;
            double c = ui->spinBox_8->value();

            sink_pdo.var.op_current = (c * 1000)/10;

            display.append(QString::number(sink_pdo.Val,16));
            ui->lineEdit->setText(display);
        }
    }

    /*append generated data objects to the display string
     * for the number of times determined by the 'no. of
     * data objects spinBox.
     */
    if(!(num == (ctr-1)))
        display.append(ch);

    ui->lineEdit_3->setText("Done. Set the next data object");
    num++;
    reset();

    /* Determine if the number of dat objects specified
     * are genearted. If yes then print a message and
     * initialise all the variables to their default values.
     */

    if(num == ctr) {
        ui->spinBox_2->setValue(0);
        ui->lineEdit_3->setText("Generated all data objects");
        display.clear();
    }
}

void PDO::on_pushButton_2_clicked()
{
    reset();
    bool ok;
    type_det.Val = ui->lineEdit_2->text().toUInt(&ok, 16);
    src_pdo.Val = ui->lineEdit_2->text().toUInt(&ok, 16);
    sink_pdo.Val = ui->lineEdit_2->text().toUInt(&ok, 16);

    if(ui->pdo_type->currentIndex() == 0)
    {
        switch(type_det.flds.sply_type)
        {
        case 0: if(src_pdo.fxd.dual_role == 1)
                ui->checkBox_6->setChecked(true);
            if(src_pdo.fxd.dual_role_pwr == 1)
                ui->checkBox->setChecked(true);
            if(src_pdo.fxd.ex_powered == 1)
                ui->checkBox_2->setChecked(true);
            if(src_pdo.fxd.usb_comm == 1)
                ui->checkBox_5->setChecked(true);
            if(src_pdo.fxd.usb_susp_sup == 1)
                ui->checkBox_3->setChecked(true);
            ui->comboBox_2->setCurrentIndex(src_pdo.fxd.current_cap);
            ui->spinBox->setValue((src_pdo.fxd.volt*50)/1000);
            ui->doubleSpinBox_2->setValue((src_pdo.fxd.cur*10)/1000);
            ui->comboBox->setCurrentIndex(src_pdo.fxd.sply_type);

            break;

        case 1: ui->spinBox_7->setValue((src_pdo.bat.max_voltage*50)/1000);
            ui->spinBox_6->setValue((src_pdo.bat.min_voltage*50)/1000);
            ui->spinBox_5->setValue((src_pdo.bat.max_power*250)/1000);
            ui->comboBox->setCurrentIndex(src_pdo.bat.supply_type);

            break;

        case 2: ui->spinBox_3->setValue((src_pdo.var.max_voltage*50)/1000);
            ui->spinBox_4->setValue((src_pdo.var.min_voltage*50)/1000);
            ui->spinBox_8->setValue((src_pdo.var.max_current*10)/1000);
            ui->comboBox->setCurrentIndex(src_pdo.var.supply_type);

            break;

        default:ui->lineEdit_3->setText("Error");
            break;
        }
    }

    else if(ui->pdo_type->currentIndex() == 1)
    {
        switch(type_det.flds.sply_type)
        {
        case 0: if(sink_pdo.fxd.dual_role_pwr)
                ui->checkBox_6->setChecked(1);
            if(sink_pdo.fxd.higher_cap)
                ui->checkBox->setChecked(1);
            if(sink_pdo.fxd.ex_powered)
                ui->checkBox_2->setChecked(1);
            if(sink_pdo.fxd.usb_comm)
                ui->checkBox_5->setChecked(1);
            if(sink_pdo.fxd.dual_role)
                ui->checkBox_3->setChecked(1);
            ui->comboBox_2->setCurrentIndex(0);
            ui->spinBox->setValue((sink_pdo.fxd.volt*50)/1000);
            ui->doubleSpinBox_2->setValue((sink_pdo.fxd.cur*10)/1000);
            ui->comboBox->setCurrentIndex(sink_pdo.fxd.supply_type);

            break;

        case 1: ui->spinBox_7->setValue((sink_pdo.bat.max_voltage*50)/1000);
            ui->spinBox_6->setValue((sink_pdo.bat.min_voltage*50)/1000);
            ui->spinBox_5->setValue((sink_pdo.bat.op_power*250)/1000);
            ui->comboBox->setCurrentIndex(sink_pdo.fxd.supply_type);

            break;

        case 2: ui->spinBox_3->setValue((sink_pdo.var.max_voltage*50)/1000);
            ui->spinBox_4->setValue((sink_pdo.var.min_voltage*50)/1000);
            ui->spinBox_8->setValue((sink_pdo.var.op_current*10)/1000);
            ui->comboBox->setCurrentIndex(sink_pdo.fxd.supply_type);

            break;

        default:ui->lineEdit_3->setText("Error");
            break;

        }
    }
}

void PDO::on_pushButton_3_pressed()
{
    ui->lineEdit->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_2->clear();
}

void PDO::on_spinBox_2_valueChanged(int arg1)
{
    ctr = arg1;
    num = 0;
}
