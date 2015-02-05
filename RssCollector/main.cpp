#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <iomanip>
#include "collector.h"

int main(int argc, char** argv) {
	std::cout << "Started" << std::endl;
	collector::Collector collector;
	collector.collectFeeds();
	std::cout << "Finished" << std::endl;
	return 0;
}

