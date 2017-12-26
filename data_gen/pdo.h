#ifndef PDO_H
#define PDO_H

#include <QWidget>

namespace Ui {
class PDO;
}

class PDO : public QWidget
{
    Q_OBJECT

public:
    explicit PDO(QWidget *parent = 0);
    ~PDO();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void reset();

    void on_spinBox_2_valueChanged(int arg1);

    void on_pushButton_3_pressed();

private:
    Ui::PDO *ui;
};

#endif // PDO_H
