#include "FinishIt.h"

std::pair <size_t, size_t> FinishIt::ends() const
{
	std::pair <size_t, size_t> min = coordinates[0], max = coordinates[0], pos = { 0, 0 };
	for (size_t i = 1; i < coordinates.size(); i++)
	{
		if (coordinates[i].first < min.first || coordinates[i].second < min.second)
		{
			min = coordinates[i];
			pos.first = i;
		}
		else if (coordinates[i].first > max.first || coordinates[i].second > max.second)
		{
			max = coordinates[i];
			pos.second = i;
		}
	}
	return pos;
}

void FinishIt::fillCloses()
{
	if (shipD == direction::Unknown)
	{
		size_t x = coordinates[0].first, y = coordinates[0].second;
		for (int i = -1; i < 2; i += 2)
		{
			try
			{
				if (bf->at(x + i, y) == Field::Status::Unknown)
					suspectedClose.push_back(std::make_pair(std::make_pair(x + i, y), bf->knownClose(x + i, y)));
			}
			catch (const std::out_of_range&) {}
			try
			{
				if (bf->at(x, y + i) == Field::Status::Unknown)
					suspectedClose.push_back(std::make_pair(std::make_pair(x, y + i), bf->knownClose(x, y + i)));
			}
			catch (const std::out_of_range&) {}
		}
	}
	else
	{
		auto shipsEnds = ends();
		size_t xs = coordinates[shipsEnds.first].first,
			ys = coordinates[shipsEnds.first].second,
			xe = coordinates[shipsEnds.second].first,
			ye = coordinates[shipsEnds.second].second;
		if (shipD == direction::Horizontal)
		{
			try
			{
				if (bf->at(xs, ys - 1) == Field::Status::Unknown)
					suspectedClose.push_back(std::make_pair(std::make_pair(xs, ys - 1), bf->knownClose(xs, ys - 1)));
			}
			catch (const std::out_of_range&) {}
			try
			{
				if (bf->at(xe, ye + 1) == Field::Status::Unknown)
					suspectedClose.push_back(std::make_pair(std::make_pair(xe, ye + 1), bf->knownClose(xe, ye + 1)));
			}
			catch (const std::out_of_range&) {}
		}
		else
		{
			try
			{
				if (bf->at(xs - 1, ys) == Field::Status::Unknown)
					suspectedClose.push_back(std::make_pair(std::make_pair(xs - 1, ys), bf->knownClose(xs - 1, ys)));
			}
			catch (const std::out_of_range&) {}
			try
			{
				if (bf->at(xe + 1, ye) == Field::Status::Unknown)
					suspectedClose.push_back(std::make_pair(std::make_pair(xe + 1, ye), bf->knownClose(xe + 1, ye)));
			}
			catch (const std::out_of_range&) {}
		}
	}
}

std::pair <size_t, size_t> FinishIt::maxElimination()
{
	if (suspectedClose.size() == 0)
	{
		fillCloses();
	}
	size_t max = suspectedClose[0].second, pos = 0;
	for (size_t i = 1; i < suspectedClose.size(); i++)
	{
		if (max < suspectedClose[i].second)
		{
			max = suspectedClose[i].second;
			pos = i;
		}
	}
	shooted = pos;
	return suspectedClose[pos].first;
}

void FinishIt::result(bool succes)
{
	if (succes)
	{
		coordinates.push_back(suspectedClose[shooted].first);
		suspectedClose.clear();
		if (shipD == direction::Unknown)
		{
			shipD = (coordinates[0].first == coordinates[1].first ? direction::Horizontal : direction::Vertical);
		}
	}
	else
	{
		suspectedClose.erase(suspectedClose.begin() + shooted);
	}
}