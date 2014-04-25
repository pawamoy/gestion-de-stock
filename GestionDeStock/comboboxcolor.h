#ifndef COMBOBOXCOLOR_H
#define COMBOBOXCOLOR_H

#include <QComboBox>
#include <string>
#include <iostream>

class ComboBoxColor
        : public QComboBox
{
public:
    ComboBoxColor(QWidget *parent, int nc);
    void SetSelection(int nc);
    int GetIndex(std::string color);
};

#endif // COMBOBOXCOLOR_H
