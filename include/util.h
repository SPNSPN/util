#ifndef UTIL_H__
#define UTIL_H__

#include <cassert>
#include <vector>
#include <numeric>
#include <algorithm>
#include <tuple>
#include <string>
#include <sstream>
#include <functional>

namespace util
{

int kbhit ();
std::vector<std::string> split (const std::string &str, char delim);
std::string join (const std::vector<std::string> &strs, const std::string &link);
double distance (const std::vector<double> &p1, const std::vector<double> &p2);

template <class T>
std::vector<T> reverse (const std::vector<T> &vec)
{
	std::vector<T> res = vec;
	std::reverse(res.begin(), res.end());
	return res;
}

template <class N, class M>
std::vector<N> range (N begin, N end, M step)
{
	if (begin > end) { return reverse(range(end, begin, -1 * step)); }

	assert(step > 0);

	std::vector<N> res;
	for (N iter = begin; iter < end; iter += step) { res.push_back(iter); }
	return res;
}

template <class N>
std::vector<N> range (N begin, N end)
{
	return range(begin, end, 1);
}

template <class T>
std::vector<T> vec ()
{
	std::vector<T> v;
	return v;
}

template <class T>
std::vector<T> vec (T head)
{
	std::vector<T> v{head};
	return v;
}

template <class T, class... Rest>
std::vector<T> vec (T head, Rest... rest)
{
	std::vector<T> v = vec(rest...);
	v.insert(v.begin(), head);
	return  v;
}

template <class T>
std::vector<T> subvector (const std::vector<T> &vec, size_t begin, size_t end)
{
	assert(begin <= end);
	assert(0 <= begin);
	assert(end <= vec.size());
	std::vector<T> svec{vec.begin() + begin, vec.begin() + end};

	return svec;
}

template <class T>
std::string vec_tostring (const std::vector<T> &vec)
{
	std::stringstream ss;

	ss << "(";
	for (auto elm = vec.begin(); elm != vec.end(); ++elm)
	{
		if (elm != vec.begin()) { ss << " "; }
		ss << *elm;
	}
	ss << ")";
	return ss.str();
}

template <class T>
std::string vec_tostring (std::vector<std::vector<T>> &vec)
{
	std::stringstream ss;

	ss << "(";
	for (auto v = vec.begin(); v != vec.end(); ++v)
	{
		if (v != vec.begin()) { ss << " "; }
		ss << vec_tostring(*v);
	}
	ss << ")";
	return ss.str();
}

template <class T>
void vec_extend (std::vector<T> &veca, const std::vector<T> &vecb)
{
	std::copy(vecb.begin(), vecb.end(), std::back_inserter(veca));
}

template <class T, class R>
std::vector<R> map (const std::function<R(T)> &proc, const std::vector<T> &vec)
{
	std::vector<R> res(vec.size());
	std::transform(vec.begin(), vec.end(), res.begin(), proc);
	return res;
}

template <class T, class R>
R reduce (const std::function<R(R, T)> &proc, const std::vector<T> &vec, const R &ini)
{
	return std::accumulate(vec.begin(), vec.end(), ini, proc);
}

template <class T, class U>
std::vector<std::pair<T, U>> zip (const std::vector<T> &t, const std::vector<U> &u)
{
	std::vector<std::pair<T, U>> res(std::min(t.size(), u.size()));
	for (size_t idx = 0; idx < res.size(); ++idx)
	{
		res.at(idx) = std::make_pair(t.at(idx), u.at(idx));
	}
	return res;
}

template <class T>
T tee (const char *format, T val)
{
	printf(format, val);
	return val;
}

}

#endif // UTIL_H__
