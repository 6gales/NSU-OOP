#pragma once
#include "bitmap/bitmap_image.hpp"
#include "Shape.h"
#include <memory>

class Drawer
{
	cartesian_canvas canvas{1, 1};
	std::string fileName;
	size_t width,
		height;
	std::vector <std::shared_ptr <shp::Shape>> figures;
public:
	Drawer(size_t _width, size_t _height);
	Drawer(size_t _width, size_t _height, std::string name);
	Drawer(std::string parameters);
	Drawer(std::string parameters, std::string name);
	void readingFigures(std::istream &is);
	void setName(std::string newName) { fileName = newName; }
	void draw(const shp::segment &line) { canvas.line_segment(line.from.first, line.from.second, line.to.first, line.to.second); }
	void draw(const shp::Shape &object);
	void drawAll();
	void saveImg() { canvas.image().save_image(fileName); }
};