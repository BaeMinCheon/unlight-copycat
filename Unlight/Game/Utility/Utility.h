#pragma once

#include <string>

#include <Core/pclaf.h>

namespace Utility
{
	static TCHAR* getTCHAR(std::string _s, std::size_t* _cn)
	{
		const char* s = _s.c_str();
		std::size_t l = _s.size() + 1;

		TCHAR* retVal = new TCHAR[l];
		mbstowcs_s(_cn, retVal, l, s, l);

		return retVal;
	}
}