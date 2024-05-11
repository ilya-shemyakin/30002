#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iostream>
#include <complex>
#include <string>

namespace nspace
{
	struct DataStruct
	{
		long long key1;
		std::complex<double> key2;
		std::string key3;
	};
	std::istream& operator>>(std::istream& in, DataStruct& dest);
	std::ostream& operator<<(std::ostream& out, const DataStruct& src);
}

#endif
