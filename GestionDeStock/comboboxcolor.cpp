#include "comboboxcolor.h"
#include "datasets.h"

ComboBoxColor::ComboBoxColor(QWidget *parent, int nc)
    : QComboBox(parent)
{
    int c;
    for (c=0; c<END_COLOR; c++)
        this->addItem(color_name[c]);

    SetSelection(nc);
}

void ComboBoxColor::SetSelection(int nc)
{
    if (nc < END_COLOR && nc != NR)
        this->setCurrentIndex(nc);
    else
        this->setCurrentIndex(END_COLOR-1);
}

int ComboBoxColor::GetIndex(std::string color)
{
    int c;
    std::string tmp;
    for(c=0; c<END_COLOR; c++)
    {
        tmp = color_name[c].toUtf8().constData();
        if( ! tmp.compare(color) )
            return c;
    }

    return -1;
}
