#pragma once
#include <iostream>
#include <math.h>
using namespace std;
template <class TYPE>
class Vec3
{
private:
	TYPE x, y, z;
public:
	// CONSTRUCTORS

	Vec3()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	Vec3(TYPE value)
	{
		x = value;
		y = value;
		z = value;
	}
	Vec3(Vec3 &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	/*Vec3(TYPE vec)
	{
		this = vec;
	}*/
	Vec3(TYPE a, TYPE b, TYPE c)
	{
		x = a;
		y = b;
		z = c;
	}
	//OPERATORS

	Vec3 operator + (const Vec3& v)
	{
		Vec3 res( x + v.x, y + v.y, z + v.z);
		return res;
	}
	Vec3 operator - (const Vec3& v)
	{
		Vec3 res(x - v.x, y - v.y, z - v.z);
		return res;
	}
	void operator += (const Vec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}
	void operator -= (const Vec3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}
	void operator = (const Vec3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	bool operator == (const Vec3& v)
	{
		if (x == v.x && y == v.y && z == v.z) return true;
		else return false;
	}

	//METHODS

	void Normalize()
	{
		float magnitude = sqrtf(x ^ 2 + y ^ 2 + z ^ 2);
		x = x / magnitude;
		y = y / magnitude;
		z = z / magnitude;
	}
	void Zero()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	bool IsZero()
	{
		if (x == 0 && y == 0 && z == 0) return true;
		else return false;
	}
	float DistanceTo(Vec3& v)
	{
		float dist = sqrtf((v.x - x) ^ 2 + (v.y - y) ^ 2 + (v.z - z) ^ 2);
		return dist;
	}
	void Draw ()
	{
		cout << "X:" << x << " Y:" << y << " Z:" << z << endl;
	}
};