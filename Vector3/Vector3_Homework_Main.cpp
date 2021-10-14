#include <iostream>
#include "Header.h"
using namespace std;

int main()
{
	Vec3 <float> v1;
	Vec3 <int> v2(1, 2, 3);
	Vec3 <float> v3(4.5f, 7.2f, 2.1f);
	Vec3 <int> v4(7, 2, 5);
	Vec3 <float> v5(3.4f, 5.1f, 0.3f);
	Vec3 <int> v2_4;
	v2_4 = v2 + v4;
	if (v1.IsZero()) cout << "v1 is Zero" << endl;

	

	
	cout << "Vector 2 ", v2.Draw();
	cout << "Vector 3 ", v3.Draw();
	cout << "Vector 4 ", v4.Draw();
	cout << "Vector 5 ", v5.Draw();

	cout << "We add v5 to v3" << endl;
		v3 += v5;
	cout << "Now v3 is: ", v3.Draw();
	cout << "We make v3 zero" << endl;
	v3.Zero();
	if (v3.IsZero()) cout << "Vector 3 is zero!", v3.Draw();
	cout << "Distance from v2 to v4 is: "<< v2.DistanceTo(v4) << endl;

	cout << "Vector 2+4 is: ",v2_4.Draw();
	cout << "Vector 2+4 is going normalized" << endl;
	v2_4.Normalize();
	cout << "Now vector 2+4 is: ", v2_4.Draw();
	

	return 0;
}