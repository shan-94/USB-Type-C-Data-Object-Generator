#include "dialog.h"
#include "form.h"
#include "pdo.h"
#include "rdo.h"
#include "vdo.h"
#include "vdo_2.h"
#include "ui_dialog.h"

#include <QTabWidget>
#include <QFileInfo>
#include <QtWidgets>
#include <QWidget>

TabDialog::TabDialog(const QString &fileName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    tabWidget = new QTabWidget;
    tabWidget->addTab(new form(), tr("Home"));
    tabWidget->addTab(new PDO(), tr("Power Delivery Data Objects"));
    tabWidget->addTab(new rdo(), tr("Request Data Objects"));
    tabWidget->addTab(new VDO_2(), tr("Vendor Defined Data Objects"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
    setWindowTitle(tr("Data Object Generator"));

    setFixedHeight(615);
    setFixedWidth(510);

}
TabDialog::~TabDialog()
{
    delete ui;
}

