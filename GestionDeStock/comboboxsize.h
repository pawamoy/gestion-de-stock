#ifndef COMBOBOXSIZE_H
#define COMBOBOXSIZE_H

#include <QComboBox>
#include <string>
#include <iostream>

class ComboBoxSize
        : public QComboBox
{
public:
    ComboBoxSize(QWidget *parent, int ns);
    void SetSelection(int ns);
    int GetIndex(int size);
};

#endif // COMBOBOXSIZE_H
