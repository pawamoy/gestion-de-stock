#include "comboboxcategory.h"
#include "datasets.h"

ComboBoxCategory::ComboBoxCategory(QWidget* parent, int nc)
    : QComboBox(parent)
{
    int c;
    for (c=0; c<END_CATEGORY; c++)
        this->addItem(category[c]);

    if (nc < END_CATEGORY)
        this->setCurrentIndex(nc);
    else
        this->setCurrentIndex(0);
}
