#include "GameManager.h"
#define _CRT_SECURE_NO_WARNINGS
int main(size_t argc, char **argv)
{
	std::vector <std::string> a = { "sss", "RandomShooter.exe", "RandomShooter.exe" };
	size_t ac = 3;
	GameManager manager{ ac, a };
	manager.begin();
	manager.showResults();
	return 0;
}

//#include <iostream>
//#include <utility> // std::pair
//#include <stdexcept>
//
//#include <boost/asio.hpp>
//#include <boost/date_time/posix_time/posix_time.hpp>
//#include <boost/process.hpp>
//
//#include <cstdlib>
//
//#define TIMEOUT 5
//
//namespace bp = boost::process;
//
//class mmm
//{
//	int timeout;
//	boost::asio::io_service io;
//	bp::opstream input;
//	boost::asio::deadline_timer timer;
//
//	bp::child child;
//	bp::async_pipe ap;
//public:
//	mmm(int t = TIMEOUT) :
//		timeout{ t },
//		io{},
//		timer{ io },
//		ap{ io }
//	{
//		try
//		{
//			child = bp::child("efff.exe",
//				bp::std_out > ap,
//				bp::std_in < input);
//		}
//		catch (const boost::process::process_error &e)
//		{
//			std::cerr << "executable not found " << e.what();
//		}
//	}
//
//	void sendMessage(std::string command)
//	{
//		input << command << std::endl;
//	}
//	// returns pair [str, is_timeout]
//	// - str contains non-line from stdin
//	// - str is empty if EOF
//	// - is_timeout is true when timeout occurs
//	std::pair<std::string, bool> readline() {
//		bool timer_result = false;
//		bool read_result = false;
//
//		timer.expires_from_now(boost::posix_time::seconds(timeout));
//		timer.async_wait([&timer_result](const boost::system::error_code& e) {
//			std::cerr << "timer result\n";
//			timer_result = (e != boost::asio::error::operation_aborted);
//		});
//
//		boost::asio::streambuf buffer;
//		boost::asio::async_read_until(
//			ap,
//			buffer,
//			'\n',
//			[&read_result](boost::system::error_code b, const long unsigned int& /*l*/) {
//			read_result = true;
//		}
//		);
//		io.reset();
//
//		while (io.run_one())
//		{
//			if (read_result)
//			{
//				timer.cancel();
//				auto size = buffer.size();
//				buffer.commit(size);
//				std::string line{
//					boost::asio::buffers_begin(buffer.data()),
//					boost::asio::buffers_end(buffer.data()),
//				};
//				return { line, false };
//			}
//			else if (timer_result)
//			{
//				return { "", true };
//			}
//		}
//		throw std::runtime_error("Unreachable");
//	}
//};
//
//int main(int argc, char ** argv) {
//	std::string sleep_arg = "1";
//	if (argc >= 2) {
//		sleep_arg = argv[1];
//	}
//	BSserver ss("ese.exe", "sss.exe", 50);
////	Player r;
////	r.sendMessage("Arrange!");
////	while (true) {
////		auto[line, timeout] = r.readline();
////		std::pair<std::string, bool> res = r.readline();
////		if (res.second) {
////			std::cerr << "Timeout reading stdin\n";
////			return 1;
////		}
////		if (res.first == "") {
////			// EOF
//////			break;
////		}
////		std::cerr << "Read: " << res.first << std::endl;
////		r.sendMessage("Shoot!");
////		res = r.readline();
////		if (res.second) {
////			std::cerr << "Timeout reading stdin\n";
////			return 1;
////		}
////		if (res.first == "") {
////			// EOF
//////			break;
////		}
////		std::cerr << "Read: " << res.first << std::endl;
//
////	}
//}

//int main()
//{
//	boost::asio::io_service ios;
//	bp::async_pipe out{ ios };
//	bp::opstream in;
////	bp::ipstream out;
//
//	bp::child c("testProj.exe", bp::std_out > out, bp::std_in < in);
//
//	in << "_ZN5boost7process8tutorialE" << std::endl;
//	std::string value;
//	std::string buf;
//	buf.resize(512, 0);
//	boost::asio::async_read(out, boost::asio::buffer(buf),
//		[](const boost::system::error_code &ec, std::size_t size) {});
//	std::cerr << buf << std::endl;
//	c.terminate();
//}


//int main()
//{
//	boost::asio::io_service ios;
//	async_pipe pipe_stream{ ios };
//
//	opstream pipe_in;
//	child c("testProj.exe", std_out > pipe_stream, std_in < pipe_in);
//	std::string line;
//	std::string buf;
//	buf.resize(1024);
//	boost::asio::async_read(pipe_stream, boost::asio::buffer(buf),
//		[](const boost::system::error_code &ec, std::size_t size) {});
//	std::cerr << buf << std::endl;
//	buf.clear();
//	pipe_in << "heh\n";
//	boost::asio::async_read(pipe_stream, boost::asio::buffer(buf),
//		[](const boost::system::error_code &ec, std::size_t size) {});
//	std::cerr << buf << std::endl;
////	c.wait();
//}
	

//std::vector<std::string> read_outline(std::string & file)
//{
//	bp::ipstream is; //reading pipe-stream
//	bp::child c("D:/hello.exe", bp::std_out > is);
//
//	std::vector<std::string> data;
//	std::string line;
//
//	while (c.running() && std::getline(is, line) && !line.empty())
//		data.push_back(line);
//
//	c.wait();
//
//	return data;
//}
//
//int main()
//{
//	boost::asio::io_service ios;
//	//std::vector<char> buf(4096);
//	std::string buf;
//	buf.resize(1024);
//	bp::async_pipe ap1(ios);
//	bp::async_pipe ap2(ios);
//	bp::opstream pp;
//	bp::ipstream ipp;
////	bp::child c("D:/testProj.exe", bp::std_out > ap1, bp::std_in < pp);
//	bp::child c("D:/testProj.exe", bp::std_out > ipp, bp::std_in < pp);
//	//boost::asio::async_read(ap1, boost::asio::buffer(buf),
//	//	[](const boost::system::error_code &ec, std::size_t size) {});
//	//ios.run();
//	ipp >> buf;
//	pp << "hi man\n";
//	ipp.clear();
//	ipp >> buf;
////	buf.clear();
////	boost::asio::async_read(ap1, boost::asio::buffer(buf),
////		[](const boost::system::error_code &ec, std::size_t size) {});
//
////	ios.run();
//	int result = c.exit_code();
//}
//
////int main(int argc, char **argv)
////{
////	//if (argc != 3)
////	//{
////	//	std::cout << "Wrong number of arguments\n";
////	//	return 1;
////	//}
////	char a;
////	boost::asio::io_service pio1;
////	
////	boost::process::opstream p1in;
////	boost::process::ipstream p1out;
////	boost::process::child ñ = boost::process::launch("")
////	boost::process::child p1("D:/Projects/source/repos/BattleshipServer/Debug/RandomShooter.exe"/*argv[1]*/, boost::process::std_out > p1out, boost::process::std_in < p1in);
////	p1in << "Arrange!";
////	std::basic_string<char> str;
////	p1out >> str;
////	std::cout << str;
////	return 0;
////}
//
////#include <boost/process.hpp>
////
////using namespace boost::process;
////
////int main()
////{
////	ipstream pipe_stream;
////	try
////	{
////		child c("gcc --version", std_out > pipe_stream);
////	}
////	catch (const boost::process::process_error &e) { std::cerr << e.what(); }
////	std::string line;
////
////	while (pipe_stream && std::getline(pipe_stream, line) && !line.empty())
////		std::cerr << line << std::endl;
////
//////	c.wait();
////}
//
////#include <iostream>
////#include <boost/asio.hpp>
////#include <boost/date_time/posix_time/posix_time.hpp>
////
////int main()
////{
////	boost::asio::io_service io;
////
////	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
////
////	t.wait();
////
////	std::cout << "Hello, world!" << std::endl;
////
////	return 0;
////}
//
////#include <vector>
////#include <boost/iostreams/device/file_descriptor.hpp>
////#include <boost/iostreams/stream.hpp>
////#include <boost/process.hpp>
////
////static const std::string PATHTOEXE = { "Unusual.exe" };
////
////int main()
////{
////	try
////	{
////		std::vector<std::string> args;
////		args.emplace_back(PATHTOEXE);
////
////		// Create pipes for stdout, stderr
//////		boost::process::pipe pstdout;
////		boost::process::pipe pstdout = boost::process::create_pipe();
////		boost::process::pipe pstderr = boost::process::create_pipe();
////
////		// Map pipe source from stdout and stderr to sources
////		boost::iostreams::file_descriptor_source sourcestdout(pstdout.source, boost::iostreams::close_handle);
////		boost::iostreams::file_descriptor_source sourcestderr(pstderr.source, boost::iostreams::close_handle);
////		
////		boost::process::opstream p1in;
////		boost::process::ipstream p1out;
////		boost::process::child p1;
////
////		// And set up streams for the sources
////		boost::iostreams::stream<boost::iostreams::file_descriptor_source> istdout(sourcestdout);
////		boost::iostreams::stream<boost::iostreams::file_descriptor_source> istderr(sourcestderr);
////
////		std::unique_ptr<boost::process::child> p;
////
////		// Want to check for process result, but also need to ensure stdin handle is closed properly,
////		// so place everything in separate scope
////		{
////			// Map pipe sink from stdout and stderr to sinks
////			boost::iostreams::file_descriptor_sink sinkstdout(pstdout.sink, boost::iostreams::close_handle);
////			boost::iostreams::file_descriptor_sink sinkstderr(pstderr.sink, boost::iostreams::close_handle);
////
////			// For stdin, map pipe to source and sink as before - want it to close on exiting this scope
////			boost::process::pipe pstdin = boost::process::create_pipe();
////			boost::iostreams::file_descriptor_source sourcestdin(pstdin.source, boost::iostreams::close_handle);
////			boost::iostreams::file_descriptor_sink sinkstdin(pstdin.sink, boost::iostreams::close_handle);
////			boost::iostreams::stream<boost::iostreams::file_descriptor_sink> ostdin(sinkstdin);
////			boost::process::child = boost::process::exe("Unusal.exe");
////			boost::process::std_
////			// Call process
////			p = std::make_unique<boost::process::child>(boost::process::execute(
////				boost::process::initializers::set_args(args),
////				boost::process::initializers::throw_on_error(),
////				boost::process::initializers::bind_stdout(sinkstdout),
////				boost::process::initializers::bind_stderr(sinkstderr),
////				boost::process::initializers::bind_stdin(sourcestdin)
////			));
////
////			// Send some test data to cin - comment out the below to test for error case
////			ostdin << "Test Input 1\n";
////			ostdin << "Some\n";
////			ostdin << "Useful\n";
////			ostdin << "Data\n";
////		}
////
////		// Check if process has exited OK - if not, report errors
////		if (boost::process::wait_for_exit(*p))
////		{
////			// Gather output from stderr
////			std::string error;
////			while (std::getline(istderr, error))
////			{
////				std::cout << "Error: " << error << '\n';
////			}
////
////			throw std::logic_error("Problem executing TestProgram...");
////		}
////
////		// Gather the output
////		std::string output;
////		while (std::getline(istdout, output))
////		{
////			std::cout << output << '\n';
////		}
////	}
////	catch (std::exception& e)
////	{
////		std::cerr << "Error: " << e.what() << '\n';
////		return 1;
////	}
////}