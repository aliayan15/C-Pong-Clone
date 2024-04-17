#include "Action.h"

Action::Action()
{
}
Action::Action(const ActionName name, const ActionType type):m_name(name),m_type(type)
{
}

const ActionName Action::name() const
{
	return m_name;
}

const ActionType Action::type() const
{
	return m_type;
}
