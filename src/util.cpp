#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "util.h"

namespace util
{

int kbhit()
{
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}
	return 0;
}

std::vector<std::string> split(const std::string &str, char delim)
{
	std::vector<std::string> res;
	size_t current = 0, found;
	while((found = str.find_first_of(delim, current))
			!= std::string::npos)
	{
		res.push_back(std::string(str, current, found - current));
		current = found + 1;
	}
	res.push_back(std::string(str, current, str.size() - current));
	return res;
}

std::string join (const std::vector<std::string> &strs, const std::string &link)
{
	std::stringstream ss;
	for (auto s = strs.begin(); s != strs.end(); ++s)
	{
		if (s != strs.begin()) { ss << link; }
		ss << *s;
	}

	return ss.str();
}

double distance (const std::vector<double> &p1, const std::vector<double> &p2)
{
	assert(p1.size() == p2.size());
	return std::sqrt(reduce<size_t, double>([=](const double &acc, const size_t &i)
			{
				return acc + std::pow(p1.at(i) - p2.at(i), 2.0);
			}, range(0UL, p1.size()), 0.0));
}

} 
