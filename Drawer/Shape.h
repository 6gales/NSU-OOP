#pragma once
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <initializer_list>
#include <cmath>
#include <limits>

namespace shp
{
	class Named
	{
		static std::map <std::string, size_t> quantity;
		std::map <std::string, size_t>::const_iterator it;
	protected:
		size_t number;
	public:
		Named(std::string name) { auto itnb = quantity.insert(std::make_pair(name, 0)); itnb.first->second++; it = itnb.first; number = it->second; }
		virtual ~Named() {}
		static size_t addName(std::string name) { auto it = quantity.insert(std::make_pair(name, 0)); it.first->second++; return it.first->second; }
		operator std::string() const { return it->first + '.' + std::to_string(number); }
	};

	class Coloured
	{
		unsigned char r, g, b;
	public:
		Coloured() { r = 0; g = 0; b = 0; }
		Coloured(std::string colour);
		virtual ~Coloured() {}
		unsigned char getRed() const { return r; }
		unsigned char getGreen() const { return g; }
		unsigned char getBlue() const { return b; }
		void setColour(std::string colour);
		void setColour(unsigned char rValue, unsigned char gValue, unsigned char bValue);
		void setRed(unsigned char value) { r = value; }
		void setGreen(unsigned char value) { g = value; }
		void setBlue(unsigned char value) { b = value; }
	};

	struct segment
	{
		std::pair<double, double> from, to;
		segment() {}
		segment(std::pair <double, double> _f, std::pair <double, double> _t) : from(_f), to(_t) {}
		segment(std::initializer_list <std::pair <double, double>> &list) { auto it = list.begin(); from = (*it); it++; to = (*it); }
	};

	class Shape : public Named, public Coloured
	{
	protected:
		std::pair <int, int> center;
	public:
		Shape(std::string name) : Named(name) { center.first = 0; center.second = 0; }
		Shape(std::string _center, std::string name, std::string colour);
		Shape(std::string name, std::string colour) : Named(name), Coloured(colour) {}
		Shape(int x, int y, std::string name, std::string colour) : Named(name), Coloured(colour) { center.first = x; center.second = y; }
		Shape(int x, int y, std::string name) : Named(name) { center.first = x; center.second = y; }
		virtual ~Shape() {}
		void setCenter(int x, int y) { center.first = x; center.second = y; }
		void setCenter(std::pair<int, int> point) { center = point; }
		virtual std::vector <segment> getSegments() const = 0;
		virtual double area() const = 0;
		virtual operator double() const = 0;
	};

	class Circle : public Shape
	{
		size_t radius;
	public:
		Circle(size_t r) : Shape("Circle"), radius(r) {}
		Circle(size_t r, int x, int y) : Shape(x, y, "Circle"), radius(r) {}
		Circle(size_t r, int x, int y, std::string colour) : Shape(x, y, "Circle", colour), radius(r) {}
		Circle(std::string _radius, std::string _center, std::string colour) : Shape(_center, "Circle", colour) { radius = std::stoul(_radius); }
		std::vector <segment> getSegments() const;
		double area() const;
		operator double() const { return area(); }
	};

	class Rectangle : public Shape
	{
		size_t length, width;
	public:
		Rectangle(size_t _length, size_t _width) : Shape("Rectangle"), length(_length), width(_width) {}
		Rectangle(size_t _length, size_t _width, int x, int y) : Shape(x, y, "Rectangle"), length(_length), width(_width) {}
		Rectangle(size_t _length, size_t _width, int x, int y, std::string colour) : Shape(x, y, "Rectangle", colour), length(_length), width(_width) {}
		Rectangle(std::string parameters, std::string _center, std::string colour);
		std::vector <segment> getSegments() const;
		double area() const;
		operator double() const { return area(); }
	};

	class Triangle : public Shape
	{
		std::pair <int, int> p1, p2;
	public:
		Triangle(int x1, int y1, int x2, int y2);
		Triangle(int x1, int y1, int x2, int y2, int x0, int y0);
		Triangle(int x1, int y1, int x2, int y2, int x0, int y0, std::string colour);
		Triangle(std::string parameters, std::string _center, std::string colour);
		std::vector <segment> getSegments() const;
		double area() const;
		operator double() const { return area(); }
	};

	class Point : public Shape
	{
	public:
		Point() : Shape("Point") {}
		Point(int x0, int y0) : Shape(x0, y0, "Point") {}
		Point(std::string colour) : Shape("Point", colour) {}
		Point(int x0, int y0, std::string colour) : Shape(x0, y0, "Point", colour) {}
		std::vector <segment> getSegments() const { return { {center, center} }; }
		double area() const { return 0; }
		operator double() const { return area(); }
	};
}

template <typename T>
std::vector <T> extractFromString(std::string str)
{
	std::vector <T> result;
	T found;
	std::stringstream temp;
	bool minus = false;
	for (size_t i = 0; i < str.size(); i++)
	{
		temp.clear();
		if (str[i] == '-')
		{
			minus = true;
			i++;
		}
		if (isdigit(str[i]))
		{
			do
			{
				temp << str[i];
				i++;
			} while (isdigit(str[i]) && (i < str.size()));
			temp >> found;
			if (minus && std::numeric_limits<T>::min() < 0)
				found = found * -1;
			result.push_back(found);
		}
		minus = false;
	}
	return result;
}

template <class T>
std::string printNames(const T &first)
{
	return static_cast<std::string>(first) + '\n';
}

template <class T, class ... args>
std::string printNames(const T &first, const args &...rest)
{
	return static_cast<std::string>(first) + '\n' + printNames(rest...);
}

template <class T>
double totalArea(const T &first)
{
	return static_cast<double>(first);
}

template <class T, class ... args>
double totalArea(const T &first, const args &...rest)
{
	return static_cast<double>(first) + totalArea(rest...);
}
