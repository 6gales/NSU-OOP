#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Bot.h"
#include <sstream>

TEST_CASE("Classic fleet")
{
	ClassicFleet fleet;
	REQUIRE(fleet == true);
	REQUIRE(fleet.maxShipSize() == 4);
	REQUIRE(fleet.boatsLeft() == false);
	fleet.destroyed(4);
	REQUIRE(fleet == true);
	REQUIRE(fleet.maxShipSize() == 3);
	REQUIRE(fleet.boatsLeft() == false);
	fleet.destroyed(2);
	REQUIRE(fleet == true);
	REQUIRE(fleet.maxShipSize() == 3);
	REQUIRE(fleet.boatsLeft() == false);
	fleet.destroyed(2);
	fleet.destroyed(3);
	fleet.destroyed(3);
	REQUIRE(fleet == true);
	REQUIRE(fleet.maxShipSize() == 2);
	REQUIRE(fleet.boatsLeft() == false);
	fleet.destroyed(2);
	REQUIRE(fleet == true);
	REQUIRE(fleet.maxShipSize() == 1);
	REQUIRE(fleet.boatsLeft() == true);
	fleet.destroyed(1);
	fleet.destroyed(1);
	fleet.destroyed(1);
	fleet.destroyed(1);
	REQUIRE(fleet == false);
}

TEST_CASE("Opponent field")
{
	Field ob(false);
	for (size_t i = 0; i < ob.size(); i++)
	{
		for (size_t j = 0; j < ob.size(); j++)
		{
			REQUIRE(ob.at(i, j) == Field::Status::Unknown);
			REQUIRE(ob.get(i, j) == Field::Status::Unknown);
		}
	}
	std::ostringstream os;
	os << Field::Status::Nothing << Field::Status::Unknown << Field::Status::Ship;
	REQUIRE(os.str() == "001");
	std::string output = "001";
	for (size_t i = 0; i < ob.size(); i++)
		output += "0000000000\n";
	os << ob;
	REQUIRE(os.str() == output);
	REQUIRE(ob.unknownLeft() == 100);
	ob.mark(std::pair<size_t, size_t>(5, 5), Field::Status::Ship);
	REQUIRE(ob.get(5, 5) == Field::Status::Ship);
	REQUIRE(ob.unknownLeft() == 99);
	REQUIRE(ob.knownClose(0, 0) == 5);
	REQUIRE(ob.knownClose(5, 5) == 0);
	REQUIRE(ob.knownClose(4, 5) == 1);
}

void shipPlacement(size_t a, size_t b, const Field &me, std::vector <std::pair <size_t, size_t>> &ship)
{
	ship.push_back(std::make_pair(a, b));
	try
	{
		if (me.at(a + 1, b) == Field::Status::Ship)
			shipPlacement(a + 1, b, me, ship);
	}
	catch (const std::out_of_range&) {}
	try
	{
		if (me.at(a, b + 1) == Field::Status::Ship)
			shipPlacement(a, b + 1, me, ship);
	}
	catch (const std::out_of_range&) {}
}

TEST_CASE("Fleet arrangment")
{
	srand(time(NULL));
	for (size_t r = 0; r < 10; r++)
	{
		const Field me(true);
		std::vector <size_t> fleet(4);
		std::vector <std::pair <size_t, size_t>> ship;
		std::vector <std::vector<size_t>> mat(10);
		for (size_t i = 0; i < 10; i++)
		{
			mat[i].resize(10);
			for (size_t j = 0; j < 10; j++)
			{
				mat[i][j] = 0;
			}
		}
		for (size_t i = 0; i < 10; i++)
		{
			for (size_t j = 0; j < 10; j++)
			{
				if (mat[i][j] == 0 && me.get(i, j) == Field::Status::Ship)
				{
					shipPlacement(i, j, me, ship);

					REQUIRE(ship.size() < 5);
					fleet[ship.size() - 1]++;
					for (size_t k = 0; k < ship.size(); k++)
					{
						mat[ship[k].first][ship[k].second] = 1;
					}
					if (ship.size() > 1)
					{
						if (ship[0].first == ship[1].first)
						{
							for (size_t k = 0; k < ship.size() - 1; k++)
							{
								REQUIRE(ship[k].first == ship[k + 1].first);
							}
						}
						else
						{
							for (size_t k = 0; k < ship.size() - 1; k++)
							{
								REQUIRE(ship[k].second == ship[k + 1].second);
							}
						}
					}
					ship.clear();
				}
			}
		}
		REQUIRE(fleet[0] == 4);
		REQUIRE(fleet[1] == 3);
		REQUIRE(fleet[2] == 2);
		REQUIRE(fleet[3] == 1);
	}
}

TEST_CASE("Diagonal strategy")
{
	Field ob{ false };
	Diagonal st(&ob);
	for (size_t i = 0; i < 24; i++)
	{
		ob.mark(st.shoot(), Field::Status::Nothing);
	}
	
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			if (i < 7 || j < 7)
			{
				bool rightX = false, rightY = false;
				for (size_t k = 0; k < 4; k++)
				{
					if (i < 7)
					{
						if (ob.get(i + k, j) == Field::Status::Nothing && !rightX)
							rightX = true;
					}
					if (j < 7)
					{
						if (ob.get(i, j + k) != Field::Status::Nothing && !rightY)
							rightY = true;
					}
				}
				REQUIRE((i < 7 ? rightX : !rightX));
				REQUIRE((j < 7 ? rightY : !rightY));
			}
		}
	}
}

TEST_CASE("BoatsLeft strategy")
{
	Field bf(false);
	BoatsLeft st(&bf);
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			bf.mark(std::make_pair(i, j), Field::Status::Nothing);
		}
	}
	for (size_t k = 0; k < 50; k++)
	{
		std::pair <size_t, size_t> point = st.shoot();
		REQUIRE(bf.get(point) == Field::Status::Unknown);
		bf.mark(point, Field::Status::Nothing);
	}
}

TEST_CASE("Finishing")
{
	Field bf(false);
	std::pair <size_t, size_t> shot = { 5, 5 };
	FinishIt ff(&bf);
	bf.mark(shot, Field::Status::Ship);
	ff.initialize(shot);
	REQUIRE(ff.maxElimination() == std::pair <size_t, size_t>(4, 5));
	bf.mark(std::pair <size_t, size_t>(4, 5), Field::Status::Nothing);
	ff.result(false);
	REQUIRE(ff.maxElimination() == std::pair <size_t, size_t>(5, 4));
	bf.mark(std::pair <size_t, size_t>(5, 4), Field::Status::Nothing);
	ff.result(false);
	REQUIRE(ff.maxElimination() == std::pair <size_t, size_t>(6, 5));
	bf.mark(std::pair <size_t, size_t>(6, 5), Field::Status::Ship);
	ff.result(true);
	REQUIRE(ff.maxElimination() == std::pair <size_t, size_t>(7, 5));
	bf.mark(std::pair <size_t, size_t>(7, 5), Field::Status::Ship);
	ff.result(true);
	REQUIRE(ff.isHorizontal() == false);
	REQUIRE(ff.shipSize() == 3);
	REQUIRE(ff.shipStart() == shot);
	ff.clear();
	REQUIRE(ff.shipSize() == 0);
}

TEST_CASE("Bot's reaction")
{
	std::ostringstream os;
	std::streambuf *backup = std::cout.rdbuf();
	std::cout.rdbuf(os.rdbuf());
	Bot pl;
	REQUIRE(pl.react("Arrange!") == true);
	auto str = os.str();
	for (size_t i = 0; i < str.size(); i++)
	{
		bool res1 = str[i] == '0' || str[i] == '1' || str[i] == '\n';
		REQUIRE(res1);
	}
	REQUIRE(pl.react("Shoot!") == true);
	str = os.str();
	str = str.substr(str.size() - 4, str.size());
	for (size_t i = 0; i < str.size(); i++)
	{
		bool res2 = (str[i] >= 'A' && str[i] <= 'J') || (str[i] >= '0' && str[i] <= '9') || str[i] == '\n' || str[i] == ' ';
		REQUIRE(res2);
	}
	str = os.str();
	REQUIRE(pl.react("Miss") == true);
	REQUIRE(str == os.str());
	REQUIRE(pl.react("Shoot!") == true);
	str = os.str();
	str = str.substr(str.size() - 4, str.size());
	for (size_t i = 0; i < str.size(); i++)
	{
		bool res3 = (str[i] >= 'A' && str[i] <= 'J') || (str[i] >= '0' && str[i] <= '9') || str[i] == '\n' || str[i] == ' ';
		REQUIRE(res3);
	}
	REQUIRE(pl.react("Hit") == true);
	str = os.str();
	str = str.substr(str.size() - 4, str.size());
	for (size_t i = 0; i < str.size(); i++)
	{
		bool res4 = (str[i] >= 'A' && str[i] <= 'J') || (str[i] >= '0' && str[i] <= '9') || str[i] == '\n' || str[i] == ' ';
		REQUIRE(res4);
	}
	REQUIRE(pl.react("Kill") == true);
	str = os.str();
	str = str.substr(str.size() - 4, str.size());
	for (size_t i = 0; i < str.size(); i++)
	{
		bool res5 = (str[i] >= 'A' && str[i] <= 'J') || (str[i] >= '0' && str[i] <= '9') || str[i] == '\n' || str[i] == ' ';
		REQUIRE(res5);
	}
	REQUIRE(pl.react("Win!") == false);
	std::cout.rdbuf(backup);
}