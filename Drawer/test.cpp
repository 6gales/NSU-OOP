#define CATCH_CONFIG_MAIN
#include "Drawer.h"
#include "catch.hpp"
#include <fstream>

TEST_CASE("extractFromString #1")
{
	auto res = extractFromString<size_t>("11, 44,21s423fdgss542ee24");
	REQUIRE(res.size() == 6);
	REQUIRE(res[0] == 11);
	REQUIRE(res[1] == 44);
	REQUIRE(res[2] == 21);
	REQUIRE(res[3] == 423);
	REQUIRE(res[4] == 542);
	REQUIRE(res[5] == 24);
}

TEST_CASE("extractFromString #2")
{
	auto res = extractFromString<int>("1 1, -44,2__$6__ 5551s-423uuu88*fdgss-542ee24");
	REQUIRE(res.size() == 10);
	REQUIRE(res[0] == 1);
	REQUIRE(res[1] == 1);
	REQUIRE(res[2] == -44);
	REQUIRE(res[3] == 2);
	REQUIRE(res[4] == 6);
	REQUIRE(res[5] == 5551);
	REQUIRE(res[6] == -423);
	REQUIRE(res[7] == 88);
	REQUIRE(res[8] == -542);
	REQUIRE(res[9] == 24);
}

TEST_CASE("Naming and counting")
{
	shp::Named a1("First"), b1("Second"), a2("First"), b2("Second");
	REQUIRE(static_cast<std::string>(a1) == "First.1");
	REQUIRE(static_cast<std::string>(a2) == "First.2");
	REQUIRE(static_cast<std::string>(b1) == "Second.1");
	REQUIRE(static_cast<std::string>(b2) == "Second.2");
}

TEST_CASE("static addName")
{
	REQUIRE(shp::Named::addName("Finish") == 1);
	REQUIRE(shp::Named::addName("Start") == 1);
	REQUIRE(shp::Named::addName("Finish") == 2);
	REQUIRE(shp::Named::addName("Start") == 2);
	shp::Named a("Finish"), b("Start");
	REQUIRE(static_cast<std::string>(a) == "Finish.3");
	REQUIRE(static_cast<std::string>(b) == "Start.3");
}

TEST_CASE("Circle name")
{
	shp::Circle o1(10), o2(15, 1, 5);
	REQUIRE(static_cast<std::string>(o1) == "Circle.1");
	REQUIRE(static_cast<std::string>(o2) == "Circle.2");
}

TEST_CASE("Rectangle name")
{
	shp::Rectangle o1(10, 20), o2(15, 15, 5, 5);
	REQUIRE(static_cast<std::string>(o1) == "Rectangle.1");
	REQUIRE(static_cast<std::string>(o2) == "Rectangle.2");
}

TEST_CASE("Triangle name")
{
	shp::Triangle o1(10, 20, 50, 40), o2(15, 15, 5, 5, 64, 64);
	REQUIRE(static_cast<std::string>(o1) == "Triangle.1");
	REQUIRE(static_cast<std::string>(o2) == "Triangle.2");
}

TEST_CASE("Point name")
{
	shp::Point o1, o2(20, 20);
	REQUIRE(static_cast<std::string>(o1) == "Point.1");
	REQUIRE(static_cast<std::string>(o2) == "Point.2");
}

TEST_CASE("printNames")
{
	shp::Named n1("Unknown"), n2("Unknown"), n3("Known");
	shp::Circle c(6);
	shp::Rectangle a(1, 1);
	shp::Triangle o1(10, 20, 50, 40), o2(15, 15, 5, 5, 64, 64);
	shp::Point p1, p2(20, 20);
	REQUIRE(printNames(o1, n1, n3, p1, p2, a, c, o2, n2) == "Triangle.3\nUnknown.1\nKnown.1\nPoint.3\nPoint.4\nRectangle.3\nCircle.3\nTriangle.4\nUnknown.2\n");
}

TEST_CASE("Circle area")
{
	shp::Circle o(117);
	REQUIRE(o.area() == 3.14159265 * 117 * 117);
}

TEST_CASE("Rectangle area")
{
	shp::Rectangle o(180, 207);
	REQUIRE(o.area() == 180 * 207);
}

TEST_CASE("Triangle area")
{
	shp::Triangle o(0, -25, 45, 0);
	REQUIRE(o.area() == 25.0 * 45.0 / 2);
}

TEST_CASE("Point area")
{
	shp::Point o1, o2(20, 20);
	REQUIRE(o1.area() == 0);
	REQUIRE(o2.area() == 0);
}

TEST_CASE("totalArea")
{

}

TEST_CASE("Coloured constructors")
{
	shp::Coloured o1("55, 55, 155"), o2("black");
	REQUIRE(o1.getRed() == 55);
	REQUIRE(o1.getGreen() == 55);
	REQUIRE(o1.getBlue() == 155);
	REQUIRE(o2.getRed() == 0);
	REQUIRE(o2.getGreen() == 0);
	REQUIRE(o2.getBlue() == 0);
}

TEST_CASE("setColour")
{
	shp::Coloured obj;
	REQUIRE(obj.getRed() == 0);
	REQUIRE(obj.getGreen() == 0);
	REQUIRE(obj.getBlue() == 0);

	obj.setRed(4);
	obj.setGreen(5);
	obj.setBlue(6);
	REQUIRE(obj.getRed() == 4);
	REQUIRE(obj.getGreen() == 5);
	REQUIRE(obj.getBlue() == 6);

	obj.setColour(7, 8, 9);
	REQUIRE(obj.getRed() == 7);
	REQUIRE(obj.getGreen() == 8);
	REQUIRE(obj.getBlue() == 9);

	obj.setColour("blue");
	REQUIRE(obj.getRed() == 0);
	REQUIRE(obj.getGreen() == 0);
	REQUIRE(obj.getBlue() == 255);

	obj.setColour("black");
	REQUIRE(obj.getRed() == 0);
	REQUIRE(obj.getGreen() == 0);
	REQUIRE(obj.getBlue() == 0);

	obj.setColour("green");
	REQUIRE(obj.getRed() == 0);
	REQUIRE(obj.getGreen() == 255);
	REQUIRE(obj.getBlue() == 0);

	obj.setColour("red");
	REQUIRE(obj.getRed() == 255);
	REQUIRE(obj.getGreen() == 0);
	REQUIRE(obj.getBlue() == 0);

	obj.setColour("white");
	REQUIRE(obj.getRed() == 255);
	REQUIRE(obj.getGreen() == 255);
	REQUIRE(obj.getBlue() == 255);

	obj.setColour("pink");
	REQUIRE(obj.getRed() == 255);
	REQUIRE(obj.getGreen() == 192);
	REQUIRE(obj.getBlue() == 203);

	obj.setColour("purple");
	REQUIRE(obj.getRed() == 128);
	REQUIRE(obj.getGreen() == 0);
	REQUIRE(obj.getBlue() == 128);

	obj.setColour("yellow");
	REQUIRE(obj.getRed() == 255);
	REQUIRE(obj.getGreen() == 255);
	REQUIRE(obj.getBlue() == 0);

	obj.setColour("gray");
	REQUIRE(obj.getRed() == 128);
	REQUIRE(obj.getGreen() == 128);
	REQUIRE(obj.getBlue() == 128);

	obj.setColour("brown");
	REQUIRE(obj.getRed() == 165);
	REQUIRE(obj.getGreen() == 42);
	REQUIRE(obj.getBlue() == 42);

	try
	{
		obj.setColour("khtonic");
	}
	catch (const std::invalid_argument&) { REQUIRE(true); }
}

TEST_CASE("segment")
{
	shp::segment a, b({ 1, 1 }, { 5, 5 }), c = { {1, 1}, {5, 5} };
	a.from = { 1, 1 };
	a.to = { 5, 5 };
	REQUIRE(a.from == b.from);
	REQUIRE(c.from == b.from);
	REQUIRE(a.to == b.to);
	REQUIRE(c.to == b.to);
}

TEST_CASE("Shape methods")
{
	shp::Point obj("green");
	REQUIRE(obj.getRed() == 0);
	REQUIRE(obj.getGreen() == 255);
	REQUIRE(obj.getBlue() == 0);
	
	obj.setCenter(11, 22);
	auto seg = obj.getSegments();
	REQUIRE(seg[0].from.first == 11);
	REQUIRE(seg[0].from.second == 22);
	REQUIRE(seg[0].from == seg[0].to);
	
	obj.setCenter({ 15, 25 });
	seg = obj.getSegments();
	REQUIRE(seg[0].from.first == 15);
	REQUIRE(seg[0].from.second == 25);
	REQUIRE(seg[0].from == seg[0].to);
}

TEST_CASE("Circle segmentation")
{
	shp::Circle o(100, 10, 10);
	auto seg = o.getSegments();
	for (size_t i = 2; i < seg.size() - 2; i++)
	{
		REQUIRE(seg[i - 2].from == seg[i].to);
	}
	REQUIRE(seg[0].to == std::pair<double, double>(-90.0, 10.0));
	REQUIRE(seg[seg.size() - 1].to == std::pair<double, double>(110.0, 10.0));
}

TEST_CASE("Rectangle segmentation")
{
	shp::Rectangle o(100, 130, 15, 15);
	auto seg = o.getSegments();
	REQUIRE(seg.size() == 4);
	REQUIRE(seg[0].from == std::pair<double, double>(-35.0, -50.0));
	REQUIRE(seg[0].to == std::pair<double, double>(-35.0, 80.0));
	REQUIRE(seg[1].from == std::pair<double, double>(-35.0, 80.0));
	REQUIRE(seg[1].to == std::pair<double, double>(65.0, 80.0));
	REQUIRE(seg[2].from == std::pair<double, double>(65.0, 80.0));
	REQUIRE(seg[2].to == std::pair<double, double>(65.0, -50.0));
	REQUIRE(seg[3].from == std::pair<double, double>(65.0, -50.0));
	REQUIRE(seg[3].to == std::pair<double, double>(-35.0, -50.0));
}

TEST_CASE("Triangle segmentation")
{
	shp::Triangle o(167, 133, 89, 17, 90, 85);
	auto seg = o.getSegments();
	REQUIRE(seg.size() == 3);
	REQUIRE(seg[0].from == std::pair<double, double>(90.0, 85.0));
	REQUIRE(seg[0].to == std::pair<double, double>(257.0, -48.0));
	REQUIRE(seg[1].from == std::pair<double, double>(257.0, -48.0));
	REQUIRE(seg[1].to == std::pair<double, double>(179.0, 68.0));
	REQUIRE(seg[2].from == std::pair<double, double>(179.0, 68.0));
	REQUIRE(seg[2].to == std::pair<double, double>(90.0, 85.0));
}

TEST_CASE("Reading exception")
{
	std::stringstream ss("Rectangle(100, 100)[40, 40]{purple}\nSquare(67)[-60, 70]{ 113, 160, 170 }\n");
	Drawer object(20, 20, "testImage.bmp");
	try
	{
		object.readingFigures(ss);
	}
	catch (const std::invalid_argument&) { REQUIRE(true); }
}

TEST_CASE("Drawing")
{
	std::ostringstream os;
	std::streambuf *back = std::cout.rdbuf();
	std::cout.rdbuf(os.rdbuf());

	std::stringstream is("Rectangle(100, 100)[40, 40]{purple}\nCircle(150)[0, 0]{ 255, 40, 169 }\nTriangle(100, 121, -142, 67)[-60, 70]{ 113, 160, 170 }\n");
	Drawer object("400x400");
	object.setName("testImage.bmp");
	object.readingFigures(is);
	object.drawAll();
	object.saveImg();

	REQUIRE(os.str() == "Drawing Rectangle.7\nWith area: 10000\nDrawing Circle.6\nWith area: 70685.8\nDrawing Triangle.7\nWith area: 11941\n");
	std::cout.rdbuf(back);
	std::ifstream ifs("testImage.bmp");
	REQUIRE(ifs);
	ifs.close();
}