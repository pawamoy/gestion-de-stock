#include "comboboxtype.h"
#include "datasets.h"

ComboBoxType::ComboBoxType(QWidget *parent, int categ)
    : QComboBox(parent)
{
    int t;

    switch (categ)
    {
    case 0:
        for (t=0; t<END_TYPE0; t++)
            this->addItem(subcategory0[t]);
        break;

    case 1:
        for (t=0; t<END_TYPE1; t++)
            this->addItem(subcategory1[t]);
        break;

    case 2:
        for (t=0; t<END_TYPE2; t++)
            this->addItem(subcategory2[t]);
        break;

    case 3:
        for (t=0; t<END_TYPE3; t++)
            this->addItem(subcategory3[t]);
        break;

    case 4:
        for (t=0; t<END_TYPE4; t++)
            this->addItem(subcategory4[t]);
        break;

    default:
        break;
    }


}
