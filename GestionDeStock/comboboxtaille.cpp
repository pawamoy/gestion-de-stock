#include "comboboxtaille.h"
#include "datasets.h"

ComboBoxTaille::ComboBoxTaille(QWidget *parent)
    : QComboBox(parent)
{
    int c;
    for (c=0; c<END_SIZE; c++)
        this->addItem(size_name[c]);
}
