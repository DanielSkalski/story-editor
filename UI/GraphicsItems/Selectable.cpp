#include "Selectable.h"

Selectable::Selectable()
    : m_IsSelected(false)
{
}

Selectable::~Selectable()
{

}

void Selectable::markAsSelected()
{
    m_IsSelected = true;
}

void Selectable::unmarkAsSelected()
{
    m_IsSelected = false;
}

bool Selectable::isSelected() const
{
    return m_IsSelected;
}
