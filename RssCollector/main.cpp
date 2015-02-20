#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <iomanip>
#include "collector.hpp"
#include "configuration.hpp"

int main(int argc, char** argv) {
    try
    {
	std::cout << "Started" << std::endl;
	
	configuration::config cfg;
	collector::Collector collector(cfg);
	collector.collectFeeds();
	std::cout << "Finished" << std::endl;
	return 0;
    }
    catch (char* e)
    {
	std::cerr << "Failed to run: " << e << std::endl;
	
    }
}
