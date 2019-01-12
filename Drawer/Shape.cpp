#include "Shape.h"

std::map <std::string, size_t> shp::Named::quantity;

shp::Coloured::Coloured(std::string colour)
{
	setColour(colour);
}

void shp::Coloured::setColour(std::string colour)
{
	auto value = extractFromString<size_t>(colour);
	if (value.size() == 3)
	{
		r = static_cast<unsigned char>(value[0]);
		g = static_cast<unsigned char>(value[1]);
		b = static_cast<unsigned char>(value[2]);
	}
	else
	{
		if (colour == "blue")
		{
			r = 0;
			g = 0;
			b = 255;
		}
		else if (colour == "black")
		{
			r = 0;
			g = 0;
			b = 0;
		}
		else if (colour == "green")
		{
			r = 0;
			g = 255;
			b = 0;
		}
		else if (colour == "red")
		{
			r = 255;
			g = 0;
			b = 0;
		}
		else if (colour == "white")
		{
			r = 255;
			g = 255;
			b = 255;
		}
		else if (colour == "pink")
		{
			r = 255;
			g = 192;
			b = 203;
		}
		else if (colour == "purple")
		{
			r = 128;
			g = 0;
			b = 128;
		}
		else if (colour == "yellow")
		{
			r = 255;
			g = 255;
			b = 0;
		}
		else if (colour == "gray" || colour == "grey")
		{
			r = 128;
			g = 128;
			b = 128;
		}
		else if (colour == "brown")
		{
			r = 165;
			g = 42;
			b = 42;
		}
		else throw std::invalid_argument("invalid colour parameters");
	}
}

void shp::Coloured::setColour(unsigned char rValue, unsigned char gValue, unsigned char bValue)
{
	r = rValue;
	g = gValue;
	b = bValue;
}

shp::Shape::Shape(std::string _center, std::string name, std::string colour) : Named(name), Coloured(colour)
{
	auto value = extractFromString<int>(_center);
	if (value.size() != 2)
		throw std::invalid_argument("invalid center parameters");
	center.first = value[0];
	center.second = value[1];
}

std::vector <shp::segment> shp::Circle::getSegments() const
{
	std::vector <segment> result;
	std::vector <std::pair <double, double>> coords(4);
	coords[0] = { center.first + 0.0 - radius, center.second + 0.0 };
	coords[2] = coords[0];
	double step = 1.0,
		start = coords[0].first + step, 
		end = center.first + 0.0 + radius;
	size_t i = 1;
	while (start < end)
	{
		coords[i % 2] = { start, (sqrt(radius * radius - (start - center.first) * (start - center.first)) + center.second) };
		coords[i % 2 + 2] = { start, 2.0 * center.second - coords[i % 2].second };
		result.push_back({ coords[i % 2], coords[(i + 1) % 2] });
		result.push_back({ coords[i % 2 + 2], coords[(i + 1) % 2 + 2] });
		start += step;
		i++;
	}
	result.push_back({ coords[--i % 2], {end, center.second} });
	result.push_back({ coords[--i % 2 + 2], {end, center.second} });
	return result;
}

double shp::Circle::area() const
{
	return 3.14159265 * radius * radius;
}

shp::Rectangle::Rectangle(std::string parameters, std::string _center, std::string colour) : Shape(_center, "Rectangle", colour)
{
	auto value = extractFromString<size_t>(parameters);
	if (value.size() != 2)
		throw std::invalid_argument("invalid rectangle parameters");
	length = value[0];
	width = value[1];
}

std::vector <shp::segment> shp::Rectangle::getSegments() const
{
	std::vector <segment> result;
	std::pair <double, double> prev = { center.first - length / 2.0, center.second - width / 2.0 };
	bool xAxis = false, sign = false;
	for (size_t i = 0; i < 4; i++)
	{
		sign = (i % 2 ? sign : !sign);
		result.push_back({ prev, {prev.first + (xAxis ? (sign ? length : -1.0 * length) : 0),
			prev.second + (!xAxis ? (sign ? width : -1.0 * width) : 0)} });
		xAxis = !xAxis;
		prev = result[i].to;
	}
	return result;
}

double shp::Rectangle::area() const
{
	return width * length;
}

shp::Triangle::Triangle(int x1, int y1, int x2, int y2) : Shape("Triangle")
{
	p1.first = center.first + x1;
	p1.second = center.second - y1;
	p2.first = center.first + x2;
	p2.second = center.second - y2;
}

shp::Triangle::Triangle(int x1, int y1, int x2, int y2, int x0, int y0) : Shape(x0, y0, "Triangle")
{
	p1.first = center.first + x1;
	p1.second = center.second - y1;
	p2.first = center.first + x2;
	p2.second = center.second - y2;
}

shp::Triangle::Triangle(int x1, int y1, int x2, int y2, int x0, int y0, std::string colour) : Shape(x0, y0, "Triangle", colour)
{
	p1.first = center.first + x1;
	p1.second = center.second - y1;
	p2.first = center.first + x2;
	p2.second = center.second - y2;
}

shp::Triangle::Triangle(std::string parameters, std::string _center, std::string colour) : Shape(_center, "Triangle", colour)
{
	auto value = extractFromString<int>(parameters);
	if (value.size() != 4)
		throw std::invalid_argument("invalid triangle parameters");
	p1.first = center.first + value[0];
	p1.second = center.second - value[1];
	p2.first = center.first + value[2];
	p2.second = center.second - value[3];
}

double shp::Triangle::area() const
{
	return 0.5 * fabs((center.first - p2.first) * (p1.second - p2.second) - (p1.first - p2.first) * (center.second - p2.second));
}

std::vector <shp::segment> shp::Triangle::getSegments() const
{
	return { {center, p1}, {p1, p2}, {p2, center} };
}