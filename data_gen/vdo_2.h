#ifndef VDO_2_H
#define VDO_2_H

#include <QWidget>
#include "vdo.h"

/*Here the vdo header file is included to enable access to the vdo class
 * so that the "discover identity" widget can be invovked from the VDO tab
 * and data can be passed to it
*/

namespace Ui {
class VDO_2;
}

class VDO_2 : public QWidget
{
    Q_OBJECT

public:
    explicit VDO_2(QWidget *parent = 0);
    ~VDO_2();

private slots:
    void on_pushButton_pressed();

    void reset();

    void on_pushButton_2_pressed();

private:
    Ui::VDO_2 *ui;
    bool ok1;
    VDO *vdo = new VDO; //creating an object of type VDO
};

#endif // VDO_2_H
