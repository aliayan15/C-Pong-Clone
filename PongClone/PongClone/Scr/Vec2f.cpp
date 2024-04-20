#include"Vec2f.h"
#include"iostream"
#include<math.h>

namespace myUtility
{
	Vec2f::Vec2f() : x(0), y(0) {};
	Vec2f::Vec2f(float x, float y) : x(x), y(y) {};

	Vec2f& Vec2f::Add(Vec2f v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	Vec2f& Vec2f::Subtract(Vec2f v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vec2f& Vec2f::Multiply(Vec2f v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}
	Vec2f& Vec2f::Scale(float v)
	{
		x *= v;
		y *= v;
		return *this;
	}
	Vec2f Vec2f::normalized()
	{
		float l = this->length();
		if (l == 0)
			return *this;
		float x = this->x / l;
		float y = this->y / l;
		return Vec2f(x, y);
	}
	Vec2f Vec2f::operator + (const Vec2f& v)
	{
		return Vec2f(x + v.x, y + v.y);
	}
	Vec2f& Vec2f::operator += (const Vec2f& v)
	{
		return Add(v);
	}
	Vec2f Vec2f::operator * (const Vec2f& v)
	{
		return Vec2f(x * v.x, y * v.y);
	}
	Vec2f& Vec2f::operator *= (const Vec2f& v)
	{
		return Multiply(v);
	}
	Vec2f Vec2f::operator * (float v)
	{
		return Vec2f(x * v, y * v);
	}
	Vec2f Vec2f::operator - (const Vec2f& v)
	{
		return Vec2f(x - v.x, y - v.y);
	}
	Vec2f& Vec2f::operator -= (const Vec2f& v)
	{
		return Subtract(v);
	}
	bool Vec2f::operator ==(const Vec2f& v)
	{
		return (x == v.x) && (y == v.y);
	}
	bool Vec2f::operator !=(const Vec2f& v)
	{
		return (x != v.x) || (y != v.y);
	}

	float Vec2f::length()
	{
		return sqrtf((x * x) + (y * y));
	}
	float Vec2f::Distance( Vec2f v)
	{
		return (*this - v).length();
	}
	float Vec2f::angleFrom(const Vec2f& v)
	{
		return atan2f(v.y - y, v.x - x);
	}
}

std::ostream& operator <<(std::ostream& stream, const myUtility::Vec2f& vek)
{
	return stream << "X:" << vek.x << ", Y:" << vek.y;
};