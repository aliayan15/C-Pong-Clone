#pragma once

namespace myUtility
{
	class Vec2f
	{
	public:
		float x = 0;
		float y = 0;

		Vec2f();
		Vec2f(float x, float y);

		Vec2f& Add(Vec2f v);
		Vec2f& Subtract(const Vec2f v);
		Vec2f& Multiply(const Vec2f v);
		Vec2f& Scale(const float v);
		Vec2f normalized();
		Vec2f operator + (const Vec2f& v);
		Vec2f& operator += (const Vec2f& v);
		Vec2f operator * (const Vec2f& v);
		Vec2f& operator *= (const Vec2f& v);
		Vec2f operator * (const float v);
		Vec2f operator - (const Vec2f& v);
		Vec2f& operator -= (const Vec2f& v);
		bool operator ==(const Vec2f& v);
		bool operator !=(const Vec2f& v);

		float length();
		float Distance(const Vec2f v);
		float angleFrom(const Vec2f& v);
	};
}
