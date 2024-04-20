#include "Action.h"

Action::Action()
{
}
Action::Action(ActionName name, ActionType type) :m_name(name), m_type(type)
{
}

ActionName Action::name() const
{
	return m_name;
}

ActionType Action::type() const
{
	return m_type;
}
