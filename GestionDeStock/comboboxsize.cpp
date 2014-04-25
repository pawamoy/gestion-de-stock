#include "comboboxsize.h"
#include "datasets.h"

ComboBoxSize::ComboBoxSize(QWidget *parent, int ns)
    : QComboBox(parent)
{
    int s;
    for (s=0; s<END_SIZE_NAME; s++)
        this->addItem(size_name[s]);

    SetSelection(ns);
}

void ComboBoxSize::SetSelection(int ns)
{
    if (ns < END_SIZE_NUM && ns != NR)
        this->setCurrentIndex(size_num[ns]);
    else
        this->setCurrentIndex(0);
}

int ComboBoxSize::GetIndex(int size)
{
    int c;
    std::string sizeLook = size_name[size_num[size]].toUtf8().constData();
    std::string tmp;
    for(c=0; c<END_SIZE_NAME; c++)
    {
        tmp = size_name[c].toUtf8().constData();
        if( ! tmp.compare(sizeLook) )
            return c;
    }

    return -1;
}
