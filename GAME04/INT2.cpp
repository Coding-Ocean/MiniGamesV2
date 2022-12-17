#include "INT2.h"
namespace GAME04 {

	INT2::INT2()
		:x(0), y(0)
	{
	}

	INT2::INT2(int x, int y)
	{
		this->x = x; this->y = y;
	}

	void INT2::set(int x, int y)
	{
		this->x = x; this->y = y;
	}

	void INT2::operator+=(const INT2& i)
	{
		x += i.x;
		y += i.y;
	}

	void INT2::operator*=(int s)
	{
		x *= s;
		y *= s;
	}

	INT2 INT2::operator*(int s) const
	{
		return INT2(x * s, y * s);
	}

	INT2 INT2::operator/(int s) const
	{
		return INT2(x / s, y / s);
	}

	INT2 INT2::operator-(const INT2& i) const
	{
		return INT2(x - i.x, y - i.y);
	}

	int INT2::sqMag()
	{
		return x * x + y * y;
	}
}