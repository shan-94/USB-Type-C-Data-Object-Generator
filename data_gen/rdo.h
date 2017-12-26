#ifndef RDO_H
#define RDO_H

#include <QWidget>

namespace Ui {
class rdo;
}

class rdo : public QWidget
{
    Q_OBJECT

public:
    explicit rdo(QWidget *parent = 0);
    ~rdo();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_pressed();

    void reset();

private:
    Ui::rdo *ui;
};

#endif // RDO_H
