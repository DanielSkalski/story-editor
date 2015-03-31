#ifndef SELECTABLE_H
#define SELECTABLE_H


class Selectable
{
protected:
    bool m_IsSelected;

public:
    Selectable();
    virtual ~Selectable();

    void markAsSelected();
    void unmarkAsSelected();
    bool isSelected() const;
};

#endif // SELECTABLE_H
