#pragma once
namespace GAME04 {

	class INT2
	{
	public:
		int x, y;
		INT2();
		INT2(int x, int y);
		void set(int x, int y);
		void operator+=(const INT2&);
		void operator*=(int s);
		INT2 operator*(int s) const;
		INT2 operator/(int s) const;
		INT2 operator-(const INT2&) const;
		int sqMag();

	};

}