#ifndef RT_INT2_H
#define RT_INT2_H

class Int2
{
public:
	int x, y;

	// Don't initialize in default constructor for speed.
	Int2() = default;

	Int2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	static const Int2 Zero;
	static const Int2 UnitX;
	static const Int2 UnitY;

	bool operator==(const Int2 &v) const
	{
		return (this->x == v.x) && (this->y == v.y);
	}

	bool operator!=(const Int2 &v) const
	{
		return (this->x != v.x) || (this->y != v.y);
	}

	Int2 operator+(const Int2 &v) const
	{
		return Int2(this->x + v.x, this->y + v.y);
	}

	Int2 operator-() const
	{
		return Int2(-this->x, -this->y);
	}

	Int2 operator-(const Int2 &v) const
	{
		return Int2(this->x - v.x, this->y - v.y);
	}

	Int2 operator*(int scale) const
	{
		return Int2(this->x * scale, this->y * scale);
	}

	Int2 operator*(const Int2 &v) const
	{
		return Int2(this->x * v.x, this->y * v.y);
	}

	Int2 operator/(int scale) const
	{
		return Int2(this->x / scale, this->y / scale);
	}

	Int2 operator/(const Int2 &v) const
	{
		return Int2(this->x / v.x, this->y / v.y);
	}
};

#endif
