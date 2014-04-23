#include "comboboxcategory.h"
#include "datasets.h"

ComboBoxCategory::ComboBoxCategory(QWidget* parent)
    : QComboBox(parent)
{
    int c;
    for (c=0; c<END_CATEGORY; c++)
        this->addItem(category[c]);
}
