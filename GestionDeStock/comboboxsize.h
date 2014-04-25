#ifndef COMBOBOXSIZE_H
#define COMBOBOXSIZE_H

#include <QComboBox>

class ComboBoxSize
        : public QComboBox
{
public:
    ComboBoxSize(QWidget *parent, int ns);
    void SetSelection(int ns);
};

#endif // COMBOBOXSIZE_H
