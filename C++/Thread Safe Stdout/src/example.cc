#include <iostream> // std::cout, std::endl, std::flush
#include <mutex> // std::mutex
#include <utility> // std::scoped_lock
#include <string> // std::string, std::move
#include <cstdlib> // EXIT_SUCCESS

/*
 * Explanation:
 * 	std::cout is inherently thread unsafe because of its buffered nature.
 * 	By forcing a stream flush with each message, and by ensuring only one thread is accessing it at a time, we can ensure proper concurrency.
 */

class ThreadSafeOutput {
public:
	ThreadSafeOutput() = default;
	~ThreadSafeOutput() = default;

	// Print to Stdout
	void print(std::string&& message)
	{
		std::scoped_lock<std::mutex> lock(this->m_mut);
		std::cout << message << std::flush;
	}
	
	// Print to Stdout with a new line
	void println(std::string&& message) 
	{
		std::scoped_lock<std::mutex> lock(this->m_mut);
		std::cout << message << std::endl;
	}

	// Print to Stdout with a referenced String
	void print(std::string& message)
	{
		this->print(std::move(message));
	}

	// Print to Stdout with a new line with a referenced String
	void println(std::string& message)
	{
		this->println(std::move(message));
	}

private:
	mutable std::mutex m_mut;
}

int main(int argc, char** argv)
{
	ThreadSafeOutput tso;
	tso.println("Test");
	return EXIT_SUCCESS;
}
