#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class QTabWidget;
class QFileInfo;

namespace Ui {
class Dialog;
class Widget;
}

class TabDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TabDialog(const QString &fileName, QWidget *parent = 0);
    ~TabDialog();
    QTabWidget *tabWidget;

private:
    Ui::Dialog *ui;

};

#endif // DIALOG_H
