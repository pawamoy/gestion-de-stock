#include "comboboxcolor.h"
#include "datasets.h"

ComboBoxColor::ComboBoxColor(QWidget *parent, int nc)
    : QComboBox(parent)
{
    int c;
    for (c=0; c<END_COLOR; c++)
        this->addItem(color_name[c]);

    if (nc < END_COLOR)
        this->setCurrentIndex(nc);
    else
        this->setCurrentIndex(0);
}
