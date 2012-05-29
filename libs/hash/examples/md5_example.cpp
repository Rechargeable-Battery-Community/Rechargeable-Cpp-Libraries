/**
 * \file fnv1a_example.cpp
 *
 * \section COPYRIGHT
 *
 * Rechargeable C++ Libraries
 *
 * ---------------------------------------------------------------------
 *
 * Copyright (c) 2012 Don Olmstead
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 *   1. The origin of this software must not be misrepresented; you must not
 *   claim that you wrote the original software. If you use this software
 *   in a product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not be
 *   misrepresented as being the original software.
 * 
 *   3. This notice may not be removed or altered from any source
 *   distribution.
 */

#include <iostream>
#include <iomanip>
#include <rechargeable/hash/md5.hpp>
#include <rechargeable/hash/string_hash.hpp>
using namespace rechargeable;

//---------------------------------------------------------------------

std::ostream& operator<< (std::ostream& output, const md5_digest& digest)
{
	for (std::size_t i = 0; i < 16; ++i)
		output << std::hex << std::setfill('0') << std::setw(2) << static_cast<std::uint32_t>(digest.digest[i]);

	return output;
}

//---------------------------------------------------------------------

void md5_hash(const char* value)
{
	std::cout << "md5(\"" << value << "\") = " << md5::hash(value) << std::endl;
}

//---------------------------------------------------------------------

void md5_function()
{
	std::cout << "Using md5::hash\n";

	md5_hash("");
	md5_hash("a");
	md5_hash("abc");
	md5_hash("message digest");
	md5_hash("abcdefghijklmnopqrstuvwxyz");
	md5_hash("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	md5_hash("12345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

//---------------------------------------------------------------------

void md5_string_hash(const char* value)
{
	string_hash<md5> hash(value);
	std::cout << "md5(\"" << value << "\") = " << hash.get_hash() << std::endl;
}

//---------------------------------------------------------------------

void md5_class()
{
	std::cout << "\nUsing string_hash<md5>\n";

	md5_string_hash("");
	md5_string_hash("a");
	md5_string_hash("abc");
	md5_string_hash("message digest");
	md5_string_hash("abcdefghijklmnopqrstuvwxyz");
	md5_string_hash("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	md5_string_hash("12345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

//---------------------------------------------------------------------

int main()
{
	md5_function();
	md5_class();
}
