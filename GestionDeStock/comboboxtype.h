#ifndef COMBOBOXTYPE_H
#define COMBOBOXTYPE_H

#include <QComboBox>
#include <string>
#include <iostream>

class ComboBoxType
        : public QComboBox
{
public:
    ComboBoxType(QWidget *parents, int nc, int nt);
    void SetSelection(int nc, int nt);
};

#endif // COMBOBOXTYPE_H
