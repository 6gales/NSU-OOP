#define _CRT_SECURE_NO_WARNINGS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <sstream>
#include "catch.hpp"
#include "TritSet.h"

TEST_CASE("Constructor")
{
	TritSet obj(1000);

	for (uint i = 0; i < 30; i++)
		obj[i] = Trit(i % 3);
	for (uint i = 600; i < 800; i++)
		obj[i] = Trit::False;
	for (uint i = 800; i < 1000; i++)
		obj[i] = Trit::True;

	for (uint i = 0; i < 30; i++)
		REQUIRE(obj[i] == Trit(i % 3));
	for (uint i = 30; i < 600; i++)
		REQUIRE(obj[i] == Trit::Unknown);
	for (uint i = 600; i < 800; i++)
		REQUIRE(obj[i] == Trit::False);
	for (uint i = 800; i < 1000; i++)
		REQUIRE(obj[i] == Trit::True);
}

TEST_CASE("Initilizer list constructor")
{
	TritSet obj = { Trit::False, Trit::True, Trit::Unknown, Trit::True, Trit::Unknown, Trit::False};
	REQUIRE(obj[0] == Trit::False);
	REQUIRE(obj[1] == Trit::True);
	REQUIRE(obj[2] == Trit::Unknown);
	REQUIRE(obj[3] == Trit::True);
	REQUIRE(obj[4] == Trit::Unknown);
	REQUIRE(obj[5] == Trit::False);
}

TEST_CASE("Single trit operator &")
{
	Trit F = Trit::False, U = Trit::Unknown, T = Trit::True;

	REQUIRE((F & F) == Trit::False);
	REQUIRE((F & U) == Trit::False);
	REQUIRE((F & T) == Trit::False);
	REQUIRE((U & U) == Trit::Unknown);
	REQUIRE((U & T) == Trit::Unknown);
	REQUIRE((T & T) == Trit::True);
}

TEST_CASE("Single trit operator |")
{
	Trit F = Trit::False, U = Trit::Unknown, T = Trit::True;

	REQUIRE((T | T) == Trit::True);
	REQUIRE((T | U) == Trit::True);
	REQUIRE((T | F) == Trit::True);
	REQUIRE((U | U) == Trit::Unknown);
	REQUIRE((U | F) == Trit::Unknown);
	REQUIRE((F | F) == Trit::False);
}

TEST_CASE("Single trit operator !")
{
	Trit F = Trit::False, U = Trit::Unknown, T = Trit::True;
	REQUIRE(!F == Trit::True);
	REQUIRE(!U == Trit::Unknown);
	REQUIRE(!T == Trit::False);
}

TEST_CASE("Single trit equality")
{
	Trit a;
	TritSet obj(2);
	obj[0] = Trit::True;
	a = obj[0];
	obj[1] = a;
	REQUIRE(obj[0] == Trit::True);
	REQUIRE(obj[1] == Trit::True);
	REQUIRE(a == Trit::True);
}

TEST_CASE("Trit ostream output")
{
	std::stringstream out;
	out << Trit::False << '\n';
	out << Trit::Unknown << '\n';
	out << Trit::True << '\n';
	REQUIRE(out.str() == "False\nUnknown\nTrue\n");
}

TEST_CASE("TritSet ostream output")
{
	std::stringstream out;
	TritSet obj(4);
	obj[0] = Trit::False;
	obj[2] = Trit::True;
	obj[3] = Trit::True;
	out << obj;
	REQUIRE(out.str() == "Trit number 0: False\nTrit number 1: Unknown\nTrit number 2: True\nTrit number 3: True\n");
}

TEST_CASE("Foreach-like for")
{
	std::stringstream out;
	TritSet obj = { Trit::False, Trit::True, Trit::Unknown, Trit::True };
	for (const Trit & t : obj)
	{
		out << t << std::endl;
	}
	REQUIRE(out.str() == "False\nTrue\nUnknown\nTrue\n");
}

TEST_CASE("Creating Unknown uint")
{
	uint u = formUnknown();
	for (uint i = (sizeof(uint) * 4); i > 0; i--)
	{
		Trit v = Trit(u & 3);
		REQUIRE(v == Trit::Unknown);
		u >>= 2;
	}
}

TEST_CASE("Dynamic memory segmentation and operators [], \"=\", \"Trit()\" #1")
{
	TritSet obj;
	
	for (uint i = 0; i < 30; i++)
		obj[i] = Trit(i % 3);
	obj[70] = Trit::True;
	obj[70] = Trit::Unknown;

	for (uint i = 0; i < 30; i++)
		REQUIRE(obj[i] == Trit(i % 3));
	for (uint i = 30; i < 100; i++)
		REQUIRE(obj[i] == Trit::Unknown);
}

TEST_CASE("Dynamic memory segmentation and operators [], \"=\", \"Trit()\" #2")
{
	TritSet obj;
	obj[0] = Trit::False;
	obj[1] = Trit::Unknown;
	obj[2] = Trit::True;
	for (uint i = 3; i < 30; i++)
		obj[i] = obj[i % 3];
	for (uint i = 0; i < 30; i++)
		REQUIRE(obj[i] == Trit(i % 3));
}

TEST_CASE("Trim #1")
{
	TritSet obj;

	for (uint i = 0; i < 100; i++)
		obj[i] = Trit::True;
	for (uint i = 60; i < 80; i++)
		obj[i] = Trit::Unknown;
	obj.trim(80);
	for (uint i = 0; i < 60; i++)
		REQUIRE(obj[i] == Trit::True);
	for (uint i = 60; i < 100; i++)
		REQUIRE(obj[i] == Trit::Unknown);
	REQUIRE(obj.length() == 60);
}

TEST_CASE("Trim #2")
{
	TritSet obj;

	for (uint i = 0; i < 80; i++)
		obj[i] = Trit::True;

	obj.trim(90);
	for (uint i = 0; i < 80; i++)
		REQUIRE(obj[i] == Trit::True);
	REQUIRE(obj.length() == 80);
}

void func(TritSet obj)
{
	obj[70] = Trit::False;
	obj[50] = Trit::True;
	obj[24] = Trit::Unknown;
	obj.trim(80);
}

TEST_CASE("Copy constructor #1")
{
	TritSet ob1(100);
	ob1[88] = Trit::True;
	ob1[70] = Trit::True;
	ob1[50] = Trit::Unknown;
	ob1[24] = Trit::False;
	uint n = ob1.capacity(), m = ob1.length();
	func(ob1);
	REQUIRE(ob1[70] == Trit::True);
	REQUIRE(ob1[50] == Trit::Unknown);
	REQUIRE(ob1[24] == Trit::False);
	REQUIRE(ob1[88] == Trit::True);
	REQUIRE(ob1.capacity() == n);
	REQUIRE(ob1.length() == m);
}

TEST_CASE("Copy constructor #2")
{
	TritSet ob1(100);
	ob1[70] = Trit::True;
	ob1[50] = Trit::Unknown;
	ob1[24] = Trit::False;
	TritSet ob2 = ob1;
	ob2[70] = Trit::False;
	ob2[50] = Trit::False;
	ob2[24] = Trit::False;
	ob2.trim(60);
	
	REQUIRE(ob1[70] == Trit::True);
	REQUIRE(ob1[50] == Trit::Unknown);
	REQUIRE(ob1[24] == Trit::False);
	REQUIRE(ob2[70] == Trit::Unknown);
	REQUIRE(ob2[50] == Trit::False);
	REQUIRE(ob2[24] == Trit::False);
	REQUIRE(ob2.length() < ob1.length());
	REQUIRE(ob1.capacity() == ob2.capacity());
}

TEST_CASE("Shrink #1")
{
	TritSet obj(100);

	for (uint i = 0; i < 70; i++)
		obj[i] = Trit::True;
	obj.shrink();

	for (uint i = 0; i < 70; i++)
		REQUIRE(obj[i] == Trit::True);
	REQUIRE(obj.capacity() == obj.length());
	REQUIRE(obj.length() == 70);
	REQUIRE(obj.capacity() == 70);
}

TEST_CASE("Shrink #2")
{
	TritSet obj(100);

	for (uint i = 0; i < 70; i++)
		obj[i] = Trit::True;
	uint n = obj.length();
	for (uint i = 50; i < 70; i++)
		obj[i] = Trit::Unknown;
	uint m = obj.length();
	obj.shrink();

	for (uint i = 0; i < 50; i++)
		REQUIRE(obj[i] == Trit::True);
	for (uint i = 50; i < 70; i++)
		REQUIRE(obj[i] == Trit::Unknown);
	REQUIRE(n == 70);
	REQUIRE(n - 20 == m);
	REQUIRE(m == obj.length());
	REQUIRE(obj.capacity() == obj.length());
}

TEST_CASE("Operator =")
{
	TritSet ob1(100), ob2;
	ob1[88] = Trit::True;
	ob1[70] = Trit::True;
	ob1[50] = Trit::Unknown;
	ob1[24] = Trit::False;
	uint n = ob1.capacity(), m = ob1.length();
	ob2 = ob1;
	ob2[70] = Trit::False;
	ob2[50] = Trit::False;
	ob2[24] = Trit::False;
	ob2.trim(60);

	REQUIRE(ob1[70] == Trit::True);
	REQUIRE(ob1[50] == Trit::Unknown);
	REQUIRE(ob1[24] == Trit::False);
	REQUIRE(ob1[88] == Trit::True);

	REQUIRE(ob2[88] == Trit::Unknown);
	REQUIRE(ob2[70] == Trit::Unknown);
	REQUIRE(ob2[50] == Trit::False);
	REQUIRE(ob2[24] == Trit::False);

	REQUIRE(ob1.capacity() == n);
	REQUIRE(ob1.length() == m);
	REQUIRE(ob2.length() < ob1.length());
	REQUIRE(ob1.capacity() == ob2.capacity());
}

TEST_CASE("Operator == #1")
{
	TritSet ob1, ob2;
	for (uint i = 0; i < 50; i++)
	{
		ob1[i] = Trit::True;
		ob2[i] = Trit::True;
	}
	REQUIRE((ob1 == ob2) == 1);
}

TEST_CASE("Operator == #2")
{
	TritSet ob1, ob2;
	for (uint i = 0; i < 50; i++)
	{
		ob1[i] = Trit::True;
		ob2[i] = Trit::True;
	}
	ob1[78] = Trit::False;
	REQUIRE((ob1 == ob2) == 0);
}

TEST_CASE("Operator == #3")
{
	TritSet ob1, ob2;
	for (uint i = 0; i < 50; i++)
	{
		ob1[i] = Trit::True;
		ob2[i] = Trit::True;
	}
	ob1[33] = Trit::False;
	REQUIRE((ob1 == ob2) == 0);
}

TEST_CASE("Operator != #1")
{
	TritSet ob1, ob2;
	for (uint i = 0; i < 50; i++)
	{
		ob1[i] = Trit::True;
		ob2[i] = Trit::True;
	}
	REQUIRE((ob1 != ob2) == 0);
}

TEST_CASE("Operator != #2")
{
	TritSet ob1, ob2;
	for (uint i = 0; i < 50; i++)
	{
		ob1[i] = Trit::True;
		ob2[i] = Trit::True;
	}
	ob1[78] = Trit::False;
	REQUIRE((ob1 != ob2) == 1);
}

TEST_CASE("Operator != #3")
{
	TritSet ob1, ob2;
	for (uint i = 0; i < 50; i++)
	{
		ob1[i] = Trit::True;
		ob2[i] = Trit::True;
	}
	ob1[33] = Trit::False;
	REQUIRE((ob1 != ob2) == 1);
}

TEST_CASE("Operator & #1")
{
	TritSet ob1, ob2, ob3;
	ob1[5] = Trit::True;
	ob1[3] = Trit::False;
	ob1[1] = Trit::False;

	ob2[9] = Trit::False;
	ob2[8] = Trit::False;
	ob2[7] = Trit::False;
	ob2[0] = Trit::True;
	ob2[3] = Trit::False;
	ob2[5] = Trit::True;
	ob2[4] = Trit::True;
	ob2[2] = Trit::False;
	uint o1l = ob1.length(), o1c = ob1.capacity(), o2l = ob2.length(), o2c = ob2.capacity();
	ob3 = ob1 & ob2;

	REQUIRE(ob1[0] == Trit::Unknown);
	REQUIRE(ob1[1] == Trit::False);
	REQUIRE(ob1[2] == Trit::Unknown);
	REQUIRE(ob1[3] == Trit::False);
	REQUIRE(ob1[4] == Trit::Unknown);
	REQUIRE(ob1[5] == Trit::True);

	REQUIRE(ob2[0] == Trit::True);
	REQUIRE(ob2[1] == Trit::Unknown);
	REQUIRE(ob2[2] == Trit::False);
	REQUIRE(ob2[3] == Trit::False);
	REQUIRE(ob2[4] == Trit::True);
	REQUIRE(ob2[5] == Trit::True);
	REQUIRE(ob2[6] == Trit::Unknown);
	REQUIRE(ob2[7] == Trit::False);
	REQUIRE(ob2[8] == Trit::False);
	REQUIRE(ob2[9] == Trit::False);
	
	REQUIRE(ob3[0] == Trit::Unknown);
	REQUIRE(ob3[1] == Trit::False);
	REQUIRE(ob3[2] == Trit::False);
	REQUIRE(ob3[3] == Trit::False);
	REQUIRE(ob3[4] == Trit::Unknown);
	REQUIRE(ob3[5] == Trit::True);
	REQUIRE(ob3[6] == Trit::Unknown);
	REQUIRE(ob3[7] == Trit::False);
	REQUIRE(ob3[8] == Trit::False);
	REQUIRE(ob3[9] == Trit::False);
	
	REQUIRE(ob2.length() == o2l);
	REQUIRE(ob1.length() == o1l);
	REQUIRE(ob1.capacity() == o1c);
	REQUIRE(ob2.capacity() == o2c);
	REQUIRE(ob3.capacity() == o2c);
	REQUIRE(ob3.length() == o2l);
}

TEST_CASE("Operator & #2")
{
	TritSet ob1, ob2, ob3;
	ob1[5] = Trit::True;
	ob1[3] = Trit::False;
	ob1[1] = Trit::False;

	ob2[0] = Trit::True;
	ob2[3] = Trit::False;
	ob2[5] = Trit::True;
	ob2[4] = Trit::True;
	ob2[2] = Trit::False;
	uint o1l = ob1.length(), o1c = ob1.capacity(), o2l = ob2.length(), o2c = ob2.capacity();
	ob3 = ob1 & ob2;

	REQUIRE(ob1[0] == Trit::Unknown);
	REQUIRE(ob1[1] == Trit::False);
	REQUIRE(ob1[2] == Trit::Unknown);
	REQUIRE(ob1[3] == Trit::False);
	REQUIRE(ob1[4] == Trit::Unknown);
	REQUIRE(ob1[5] == Trit::True);

	REQUIRE(ob2[0] == Trit::True);
	REQUIRE(ob2[1] == Trit::Unknown);
	REQUIRE(ob2[2] == Trit::False);
	REQUIRE(ob2[3] == Trit::False);
	REQUIRE(ob2[4] == Trit::True);
	REQUIRE(ob2[5] == Trit::True);

	REQUIRE(ob3[0] == Trit::Unknown);
	REQUIRE(ob3[1] == Trit::False);
	REQUIRE(ob3[2] == Trit::False);
	REQUIRE(ob3[3] == Trit::False);
	REQUIRE(ob3[4] == Trit::Unknown);
	REQUIRE(ob3[5] == Trit::True);
	
	REQUIRE(ob2.length() == o2l);
	REQUIRE(ob1.length() == o1l);
	REQUIRE(ob1.capacity() == o1c);
	REQUIRE(ob2.capacity() == o2c);
	REQUIRE(ob3.capacity() == o2c);
	REQUIRE(ob3.length() == o2l);
}

TEST_CASE("Operator &=")
{
	TritSet ob1, ob2;
	ob1[5] = Trit::True;
	ob1[3] = Trit::False;
	ob1[1] = Trit::False;

	ob2[9] = Trit::False;
	ob2[8] = Trit::False;
	ob2[7] = Trit::False;
	ob2[0] = Trit::True;
	ob2[3] = Trit::False;
	ob2[5] = Trit::True;
	ob2[4] = Trit::True;
	ob2[2] = Trit::False;
	uint o2l = ob2.length(), o2c = ob2.capacity();
	ob1 &= ob2;

	REQUIRE(ob2[0] == Trit::True);
	REQUIRE(ob2[1] == Trit::Unknown);
	REQUIRE(ob2[2] == Trit::False);
	REQUIRE(ob2[3] == Trit::False);
	REQUIRE(ob2[4] == Trit::True);
	REQUIRE(ob2[5] == Trit::True);
	REQUIRE(ob2[6] == Trit::Unknown);
	REQUIRE(ob2[7] == Trit::False);
	REQUIRE(ob2[8] == Trit::False);
	REQUIRE(ob2[9] == Trit::False);

	REQUIRE(ob1[0] == Trit::Unknown);
	REQUIRE(ob1[1] == Trit::False);
	REQUIRE(ob1[2] == Trit::False);
	REQUIRE(ob1[3] == Trit::False);
	REQUIRE(ob1[4] == Trit::Unknown);
	REQUIRE(ob1[5] == Trit::True);
	REQUIRE(ob1[6] == Trit::Unknown);
	REQUIRE(ob1[7] == Trit::False);
	REQUIRE(ob1[8] == Trit::False);
	REQUIRE(ob1[9] == Trit::False);

	REQUIRE(ob2.length() == o2l);
	REQUIRE(ob2.capacity() == o2c);
	REQUIRE(ob1.capacity() == o2c);
	REQUIRE(ob1.length() == o2l);
}

TEST_CASE("Operator | #1")
{
	TritSet ob1, ob2, ob3;
	ob1[5] = Trit::True;
	ob1[3] = Trit::False;
	ob1[1] = Trit::False;

	ob2[9] = Trit::False;
	ob2[8] = Trit::False;
	ob2[7] = Trit::False;
	ob2[0] = Trit::True;
	ob2[3] = Trit::False;
	ob2[5] = Trit::True;
	ob2[4] = Trit::True;
	ob2[2] = Trit::False;
	uint o1l = ob1.length(), o1c = ob1.capacity(), o2l = ob2.length(), o2c = ob2.capacity();
	ob3 = ob1 | ob2;

	REQUIRE(ob1[0] == Trit::Unknown);
	REQUIRE(ob1[1] == Trit::False);
	REQUIRE(ob1[2] == Trit::Unknown);
	REQUIRE(ob1[3] == Trit::False);
	REQUIRE(ob1[4] == Trit::Unknown);
	REQUIRE(ob1[5] == Trit::True);

	REQUIRE(ob2[0] == Trit::True);
	REQUIRE(ob2[1] == Trit::Unknown);
	REQUIRE(ob2[2] == Trit::False);
	REQUIRE(ob2[3] == Trit::False);
	REQUIRE(ob2[4] == Trit::True);
	REQUIRE(ob2[5] == Trit::True);
	REQUIRE(ob2[6] == Trit::Unknown);
	REQUIRE(ob2[7] == Trit::False);
	REQUIRE(ob2[8] == Trit::False);
	REQUIRE(ob2[9] == Trit::False);

	REQUIRE(ob3[0] == Trit::True);
	REQUIRE(ob3[1] == Trit::Unknown);
	REQUIRE(ob3[2] == Trit::Unknown);
	REQUIRE(ob3[3] == Trit::False);
	REQUIRE(ob3[4] == Trit::True);
	REQUIRE(ob3[5] == Trit::True);
	REQUIRE(ob3[6] == Trit::Unknown);
	REQUIRE(ob3[7] == Trit::Unknown);
	REQUIRE(ob3[8] == Trit::Unknown);
	REQUIRE(ob3[9] == Trit::Unknown);

	REQUIRE(ob2.length() == o2l);
	REQUIRE(ob1.length() == o1l);
	REQUIRE(ob1.capacity() == o1c);
	REQUIRE(ob2.capacity() == o2c);
	REQUIRE(ob3.capacity() == o2c);
	REQUIRE(ob3.length() == 6);
}

TEST_CASE("Operator | #2")
{
	TritSet ob1, ob2, ob3;
	ob1[5] = Trit::True;
	ob1[3] = Trit::False;
	ob1[1] = Trit::False;

	ob2[0] = Trit::True;
	ob2[3] = Trit::False;
	ob2[5] = Trit::True;
	ob2[4] = Trit::True;
	ob2[2] = Trit::False;
	uint o1l = ob1.length(), o1c = ob1.capacity(), o2l = ob2.length(), o2c = ob2.capacity();
	ob3 = ob1 | ob2;

	REQUIRE(ob1[0] == Trit::Unknown);
	REQUIRE(ob1[1] == Trit::False);
	REQUIRE(ob1[2] == Trit::Unknown);
	REQUIRE(ob1[3] == Trit::False);
	REQUIRE(ob1[4] == Trit::Unknown);
	REQUIRE(ob1[5] == Trit::True);

	REQUIRE(ob2[0] == Trit::True);
	REQUIRE(ob2[1] == Trit::Unknown);
	REQUIRE(ob2[2] == Trit::False);
	REQUIRE(ob2[3] == Trit::False);
	REQUIRE(ob2[4] == Trit::True);
	REQUIRE(ob2[5] == Trit::True);

	REQUIRE(ob3[0] == Trit::True);
	REQUIRE(ob3[1] == Trit::Unknown);
	REQUIRE(ob3[2] == Trit::Unknown);
	REQUIRE(ob3[3] == Trit::False);
	REQUIRE(ob3[4] == Trit::True);
	REQUIRE(ob3[5] == Trit::True);

	REQUIRE(ob2.length() == o2l);
	REQUIRE(ob1.length() == o1l);
	REQUIRE(ob1.capacity() == o1c);
	REQUIRE(ob2.capacity() == o2c);
	REQUIRE(ob3.capacity() == o2c);
	REQUIRE(ob3.length() == 6);
}

TEST_CASE("Operator |=")
{
	TritSet ob1, ob2;
	ob1[5] = Trit::True;
	ob1[3] = Trit::False;
	ob1[1] = Trit::False;

	ob2[9] = Trit::False;
	ob2[8] = Trit::False;
	ob2[7] = Trit::False;
	ob2[0] = Trit::True;
	ob2[3] = Trit::False;
	ob2[5] = Trit::True;
	ob2[4] = Trit::True;
	ob2[2] = Trit::False;
	ob2[6] = Trit::True;
	uint o2l = ob2.length(), o2c = ob2.capacity();
	ob1 |= ob2;

	REQUIRE(ob2[0] == Trit::True);
	REQUIRE(ob2[1] == Trit::Unknown);
	REQUIRE(ob2[2] == Trit::False);
	REQUIRE(ob2[3] == Trit::False);
	REQUIRE(ob2[4] == Trit::True);
	REQUIRE(ob2[5] == Trit::True);
	REQUIRE(ob2[6] == Trit::True);
	REQUIRE(ob2[7] == Trit::False);
	REQUIRE(ob2[8] == Trit::False);
	REQUIRE(ob2[9] == Trit::False);

	REQUIRE(ob1[0] == Trit::True);
	REQUIRE(ob1[1] == Trit::Unknown);
	REQUIRE(ob1[2] == Trit::Unknown);
	REQUIRE(ob1[3] == Trit::False);
	REQUIRE(ob1[4] == Trit::True);
	REQUIRE(ob1[5] == Trit::True);
	REQUIRE(ob1[6] == Trit::True);
	REQUIRE(ob1[7] == Trit::Unknown);
	REQUIRE(ob1[8] == Trit::Unknown);
	REQUIRE(ob1[9] == Trit::Unknown);

	REQUIRE(ob2.length() == o2l);
	REQUIRE(ob2.capacity() == o2c);
	REQUIRE(ob1.capacity() == 7);
	REQUIRE(ob1.length() == 7);
}

TEST_CASE("Operator !")
{
	TritSet ob1(100);
	ob1[0] = Trit::True;
	ob1[2] = ob1[0];
	ob1[1] = Trit::False;
	ob1[5] = Trit::False;
	TritSet ob2 = !ob1;
	
	REQUIRE(ob1.length() == 6);
	REQUIRE(ob1.length() == ob2.length());

	REQUIRE(ob1[0] == Trit::True);
	REQUIRE(ob1[1] == Trit::False);
	REQUIRE(ob1[2] == Trit::True);
	REQUIRE(ob1[3] == Trit::Unknown);
	REQUIRE(ob1[4] == Trit::Unknown);
	REQUIRE(ob1[5] == Trit::False);

	REQUIRE(ob2[0] == Trit::False);
	REQUIRE(ob2[1] == Trit::True);
	REQUIRE(ob2[2] == Trit::False);
	REQUIRE(ob2[3] == Trit::Unknown);
	REQUIRE(ob2[4] == Trit::Unknown);
	REQUIRE(ob2[5] == Trit::True);
}

TEST_CASE("Cardinality")
{
	TritSet obj;
	obj[22] = Trit::False;
	obj[19] = Trit::True;
	obj[18] = Trit::True;
	obj[16] = Trit::False;
	obj[14] = Trit::True;
	obj[13] = Trit::True;
	obj[12] = Trit::True;
	obj[9] = Trit::False;
	obj[8] = Trit::False;
	obj[7] = Trit::False;
	obj[5] = Trit::True;
	obj[4] = Trit::True;
	obj[3] = Trit::False;
	obj[2] = Trit::False;
	obj[0] = Trit::True;

	REQUIRE(obj.cardinality(Trit::False) == 7);
	REQUIRE(obj.cardinality(Trit::Unknown) == 8);
	REQUIRE(obj.cardinality(Trit::True) == 8);
}

TEST_CASE("Map cardinality")
{
	TritSet obj;
	obj[22] = Trit::False;
	obj[19] = Trit::True;
	obj[18] = Trit::True;
	obj[16] = Trit::False;
	obj[14] = Trit::True;
	obj[13] = Trit::True;
	obj[12] = Trit::True;
	obj[9] = Trit::False;
	obj[8] = Trit::False;
	obj[7] = Trit::False;
	obj[5] = Trit::True;
	obj[4] = Trit::True;
	obj[3] = Trit::False;
	obj[2] = Trit::False;
	obj[0] = Trit::True;

	std::unordered_map<Trit, int, EnumClassHash> count = obj.cardinality();

	REQUIRE(count[Trit::False]  == 7);
	REQUIRE(count[Trit::Unknown] == 8);
	REQUIRE(count[Trit::True] == 8);
}