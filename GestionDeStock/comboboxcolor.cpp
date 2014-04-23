#include "comboboxcolor.h"
#include "datasets.h"

ComboBoxColor::ComboBoxColor(QWidget *parent)
    : QComboBox(parent)
{
    int c;
    for (c=0; c<END_COLOR; c++)
        this->addItem(color_name[c]);
}
