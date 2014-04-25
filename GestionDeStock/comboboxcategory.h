#ifndef COMBOBOXCATEGORY_H
#define COMBOBOXCATEGORY_H

#include <QComboBox>

class ComboBoxCategory
        : public QComboBox
{
public:
    ComboBoxCategory(QWidget* parent, int nc);
    void SetSelection(int nc);
    int GetIndex(std::string cat);
};

#endif // COMBOBOXCATEGORY_H
