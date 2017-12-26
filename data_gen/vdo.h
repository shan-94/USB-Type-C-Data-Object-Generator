#ifndef VDO_H
#define VDO_H

#include <QWidget>

namespace Ui {
class VDO;
}

class VDO : public QWidget
{
    Q_OBJECT

public:
    explicit VDO(QWidget *parent = 0);
    ~VDO();

public slots:
    void getText(QString txt);

private slots:
    void reset();

    void reset_2();

    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_2_pressed();

private:
    Ui::VDO *ui;
    bool ok;
};

#endif // VIDO_H
