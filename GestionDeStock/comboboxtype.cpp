#include "comboboxtype.h"
#include "datasets.h"

ComboBoxType::ComboBoxType(QWidget *parent, int nc, int nt)
    : QComboBox(parent)
{
    int t;

    switch (nc)
    {
    case INTERVETEMENT:
        for (t=0; t<END_TYPE1; t++)
            this->addItem(subcategory1[t]);
        break;

    case VETEMENT1:
    case VETEMENT2:
    case VETEMENT3:
    case VETEMENT4:
        for (t=0; t<END_TYPE2; t++)
            this->addItem(subcategory2[t]);
        break;

    case SURVETEMENT1:
    case SURVETEMENT2:
    case SURVETEMENT3:
        for (t=0; t<END_TYPE3; t++)
            this->addItem(subcategory3[t]);
        break;

    case ENSEMBLE:
        for (t=0; t<END_TYPE4; t++)
            this->addItem(subcategory4[t]);
        break;

    case SOUSVETEMENT:
    default:
        for (t=0; t<END_TYPE0; t++)
            this->addItem(subcategory0[t]);
        break;
    }

    SetSelection(nc, nt);
}

void ComboBoxType::SetSelection(int nc, int nt)
{
    bool set = false;
    int max;

    if (nt != NR)
    {
        switch (nc)
        {
        case INTERVETEMENT:
            if (nt < END_TYPE1) set = true;
            else max = END_TYPE1-1;
            break;

        case VETEMENT1:
        case VETEMENT2:
        case VETEMENT3:
        case VETEMENT4:
            if (nt < END_TYPE2) set = true;
            else max = END_TYPE2-1;
            break;

        case SURVETEMENT1:
        case SURVETEMENT2:
        case SURVETEMENT3:
            if (nt < END_TYPE3) set = true;
            else max = END_TYPE3-1;
            break;

        case ENSEMBLE:
            if (nt < END_TYPE4) set = true;
            else max = END_TYPE4-1;
            break;

        case SOUSVETEMENT:
        default:
            if (nt < END_TYPE0) set = true;
            else max = END_TYPE0-1;
            break;
        }

        if (set == true)
            this->setCurrentIndex(nt);
        else
            this->setCurrentIndex(max);
    }
}
