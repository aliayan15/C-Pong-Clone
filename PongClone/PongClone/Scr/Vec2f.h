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
		Vec2f& Subtract(Vec2f v);
		Vec2f& Multiply(Vec2f v);
		Vec2f& Scale(float v);
		Vec2f normalized();

		float length();
		float Distance(Vec2f v);
		float angleFrom(const Vec2f& v);

		Vec2f operator + (const Vec2f& v);
		Vec2f& operator += (const Vec2f& v);
		Vec2f operator * (const Vec2f& v);
		Vec2f& operator *= (const Vec2f& v);
		Vec2f operator * (float v);
		Vec2f operator - (const Vec2f& v);
		Vec2f& operator -= (const Vec2f& v);
		bool operator ==(const Vec2f& v);
		bool operator !=(const Vec2f& v);
	};
}
