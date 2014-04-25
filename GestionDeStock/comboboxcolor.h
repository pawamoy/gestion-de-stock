#ifndef COMBOBOXCOLOR_H
#define COMBOBOXCOLOR_H

#include <QComboBox>

class ComboBoxColor
        : public QComboBox
{
public:
    ComboBoxColor(QWidget *parent, int nc);
    void SetSelection(int nc);
};

#endif // COMBOBOXCOLOR_H
