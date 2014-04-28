#include "comboboxcategory.h"
#include "datasets.h"

ComboBoxCategory::ComboBoxCategory(QWidget* parent, int nc)
    : QComboBox(parent)
{
    int c;
    for (c=0; c<END_CATEGORY; c++)
        this->addItem(category[c]);

    SetSelection(nc);
}

void ComboBoxCategory::SetSelection(int nc)
{
    if (nc < END_CATEGORY && nc != NR)
        this->setCurrentIndex(nc);
    else
        this->setCurrentIndex(END_CATEGORY-1);
}
