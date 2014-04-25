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

    if (nt != NR)
    {
        switch (nc)
        {
        case INTERVETEMENT:
            if (nt < END_TYPE1) set = true;
            break;

        case VETEMENT1:
        case VETEMENT2:
        case VETEMENT3:
        case VETEMENT4:
            if (nt < END_TYPE2) set = true;
            break;

        case SURVETEMENT1:
        case SURVETEMENT2:
        case SURVETEMENT3:
            if (nt < END_TYPE3) set = true;
            break;

        case ENSEMBLE:
            if (nt < END_TYPE4) set = true;
            break;

        case SOUSVETEMENT:
        default:
            if (nt < END_TYPE0) set = true;
            break;
        }
    }

    if (set == true)
        this->setCurrentIndex(nt);
    else
        this->setCurrentIndex(0);
}

int ComboBoxType::GetIndex(int cat, std::string type)
{
    int t;
    std::string tmp;

    switch (cat)
    {
    case INTERVETEMENT:
        for (t=0; t<END_TYPE1; t++)
        {
            tmp = subcategory1[t].toUtf8().constData();
            if( ! tmp.compare(type) )
                return t;
        }
        break;

    case VETEMENT1:
    case VETEMENT2:
    case VETEMENT3:
    case VETEMENT4:
        for (t=0; t<END_TYPE2; t++)
        {
            tmp = subcategory2[t].toUtf8().constData();
            if( ! tmp.compare(type) )
                return t;
        }
        break;

    case SURVETEMENT1:
    case SURVETEMENT2:
    case SURVETEMENT3:
        for (t=0; t<END_TYPE3; t++)
        {
            tmp = subcategory3[t].toUtf8().constData();
            if( ! tmp.compare(type) )
                return t;
        }
        break;

    case ENSEMBLE:
        for (t=0; t<END_TYPE4; t++)
        {
            tmp = subcategory4[t].toUtf8().constData();
            if( ! tmp.compare(type) )
                return t;
        }
        break;

    case SOUSVETEMENT:
    default:
        for (t=0; t<END_TYPE0; t++)
        {
            tmp = subcategory0[t].toUtf8().constData();
            if( ! tmp.compare(type) )
                return t;
        }
        break;
    }

    return -1;

}
