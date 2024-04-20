#pragma once

enum class ActionType
{
	Pressed,
	Released
};
enum class ActionName
{
	UP,
	DOWN,
	ENTER,
	SPACE,
	W,
	S
};

struct Action
{
public:
	Action();
	Action(ActionName name, ActionType type);
	ActionName name() const;
	ActionType type() const;
private:
	ActionName m_name;
	ActionType m_type;
};