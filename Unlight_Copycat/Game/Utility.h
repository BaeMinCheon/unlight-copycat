#pragma once

#include "pclaf.h"

#include <string>

static TCHAR* stringToTCHAR(std::string& s, std::size_t n)
{
	const char* temp = s.c_str();

	std::size_t length = s.size() + 1;
	TCHAR* retVal = new TCHAR[length];
	mbstowcs_s(&n, retVal, length, temp, length);

	return retVal;
}