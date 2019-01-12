#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/process.hpp>
#include "ServerField.h"

class Player
{
	const std::string name;
	
	size_t timeout;
	boost::asio::io_service io;
	
	boost::process::child bot;

	boost::process::opstream input;
	boost::process::async_pipe output;
	
	boost::asio::deadline_timer timer;
public:
	Player(std::string playerName, size_t t = 1) : timeout{ t }, timer{ io }, output{ io }, name{ playerName }
	{
		try
		{
			bot = boost::process::child(playerName, boost::process::std_out > output, boost::process::std_in < input);
		}
		catch (const boost::process::process_error&) { throw; }
	}

	std::string getName() { return name; }

	void sendMessage(std::string command)
	{
		input << command << std::endl;
	}
	
	std::string getAnswer()
	{
		bool timer_result = false, 
			read_result = false;

		timer.expires_from_now(boost::posix_time::seconds(timeout));

		timer.async_wait([&timer_result](const boost::system::error_code& e)
		{
			timer_result = (e != boost::asio::error::operation_aborted);
		});

		boost::asio::streambuf buffer;
		boost::asio::async_read_until(output, buffer, '\n',
			[&read_result](boost::system::error_code b, const long unsigned int&) { read_result = true; });
		io.reset();

		while (io.run_one())
		{
			if (read_result)
			{
				timer.cancel();
				auto size = buffer.size();
				buffer.commit(size);
				return std::string{ boost::asio::buffers_begin(buffer.data()), boost::asio::buffers_end(buffer.data()) };

			}
			else if (timer_result)
				throw std::runtime_error("timeout");
		}
		throw std::runtime_error("unreachable");
	}
};

struct MessageSet
{
	std::string arrange = "Arrange!",
		shoot = "Shoot!",
		hit = "Hit",
		kill = "Kill",
		miss = "Miss",
		enemy = "Enemy shooted at ",
		win = "Win!",
		lose = "Lose";
};

class BSserver
{
	const MessageSet commands;
	const std::chrono::milliseconds delay;

	Player player1,
		player2;

	ServerField p1field,
		p2field;

	bool turn = true;

	bool readField(Player *pp, ServerField *fp);
	void printFields();
	std::pair <size_t, size_t> convertShot(std::string answer);
public:
	BSserver(std::string p1name, std::string p2name, size_t _delay) try : player1{ p1name }, player2{ p2name }, delay{ _delay } {}
	catch (const boost::process::process_error&) { throw; }

	std::pair <bool, bool> startGame();
};