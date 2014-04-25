#include "comboboxsize.h"
#include "datasets.h"

ComboBoxSize::ComboBoxSize(QWidget *parent, int ns)
    : QComboBox(parent)
{
    int s;
    for (s=0; s<END_SIZE; s++)
        this->addItem(size_name[s]);

    if (ns < END_SIZE)
        this->setCurrentIndex(ns);
    else
        this->setCurrentIndex(0);
}
