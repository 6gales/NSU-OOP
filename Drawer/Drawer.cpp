#include "Drawer.h"

Drawer::Drawer(size_t _width, size_t _height)
{
	fileName = "example.bmp";
	width = _width;
	height = _height;
	canvas.set_widthheight(width, height);
	canvas.pen_width(1);
	canvas.pen_color(0, 0, 0);
	canvas.line_segment(-static_cast<double>(width) / 2, 0, static_cast<double>(width) / 2, 0);
	canvas.line_segment(0, -static_cast<double>(height) / 2, 0, static_cast<double>(height) / 2);
}

Drawer::Drawer(size_t _width, size_t _height, std::string name)
{
	width = _width;
	height = _height;
	fileName = name;
	canvas.set_widthheight(width, height);
	canvas.pen_width(1);
	canvas.pen_color(0, 0, 0);
	canvas.line_segment(-static_cast<double>(width) / 2, 0, static_cast<double>(width) / 2, 0);
	canvas.line_segment(0, -static_cast<double>(height) / 2, 0, static_cast<double>(height) / 2);
}

Drawer::Drawer(std::string parameters)
{
	auto value = extractFromString<size_t>(parameters);
	if (value.size() != 2)
		throw std::invalid_argument("invalid canvas parameters");
	canvas.set_widthheight(value[0], value[1]);
	width = value[0];
	height = value[1];
	fileName = "example.bmp";
	canvas.pen_width(1);
	canvas.pen_color(0, 0, 0);
	canvas.line_segment(-static_cast<double>(width) / 2, 0, static_cast<double>(width) / 2, 0);
	canvas.line_segment(0, -static_cast<double>(height) / 2, 0, static_cast<double>(height) / 2);
}

Drawer::Drawer(std::string parameters, std::string name)
{
	auto value = extractFromString<size_t>(parameters);
	if (value.size() != 2)
		throw std::invalid_argument("invalid canvas parameters");
	canvas.set_widthheight(value[0], value[1]);	width = value[0];
	height = value[1];
	fileName = name;
	canvas.pen_width(1);
	canvas.pen_color(0, 0, 0);
	canvas.line_segment(-static_cast<double>(width) / 2, 0, static_cast<double>(width) / 2, 0);
	canvas.line_segment(0, -static_cast<double>(height) / 2, 0, static_cast<double>(height) / 2);
}

void Drawer::readingFigures(std::istream &is)
{
	std::string data;
	const std::string circle = "Circle", rectangle = "Rectangle", triangle = "Triangle";
	std::shared_ptr <shp::Shape> newFigure;
	while (is.good())
	{
		getline(is, data);
		if (!data.empty())
		{
			auto oC = data.find('('),
				cC = data.find(')'),
				oS = data.find('['),
				cS = data.find(']'),
				oF = data.find('{'),
				cF = data.find('}');
			if (data.substr(0, circle.size()) == circle)
			{
				newFigure.reset(new shp::Circle(data.substr(oC + 1, cC - oC - 1), data.substr(oS + 1, cS - oS - 1), data.substr(oF + 1, cF - oF - 1)));
			}
			else if (data.substr(0, rectangle.size()) == rectangle)
			{
				newFigure.reset(new shp::Rectangle(data.substr(oC + 1, cC - oC - 1), data.substr(oS + 1, cS - oS - 1), data.substr(oF + 1, cF - oF - 1)));
			}
			else if (data.substr(0, triangle.size()) == triangle)
			{
				newFigure.reset(new shp::Triangle(data.substr(oC + 1, cC - oC - 1), data.substr(oS + 1, cS - oS - 1), data.substr(oF + 1, cF - oF - 1)));
			}
			else throw std::invalid_argument("Shape not found");
			figures.push_back(newFigure);
		}
	}
}

void Drawer::draw(const shp::Shape &object)
{
	std::vector <shp::segment> lines = object.getSegments();
	canvas.pen_width(1);
	canvas.pen_color(object.getRed(), object.getGreen(), object.getBlue());
	std::cout << "Drawing " << printNames(object) << "With area: " << object.area() << std::endl;
	for (size_t i = 0; i < lines.size(); i++)
		draw(lines[i]);
}

void Drawer::drawAll()
{
	for (size_t i = 0; i < figures.size(); i++)
	{
		draw(*figures[i]);
	}
}