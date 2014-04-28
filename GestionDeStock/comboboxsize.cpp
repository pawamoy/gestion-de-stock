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
    if (ns == NR)
        this->setCurrentIndex(END_SIZE_NAME);
    else if (ns < END_SIZE_NUM)
        this->setCurrentIndex(size_num[ns]);
    else
        this->setCurrentIndex(END_SIZE_NAME-1);
}

int ComboBoxSize::GetIndex(int selection)
{
    int i, res = -1;
    for (i=0; i<END_SIZE_NUM; i++)
    {
        if (size_num[i] == selection)
        {
            res = i;
            break;
        }
    }
    return res;
}
