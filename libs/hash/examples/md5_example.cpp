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

#include <rechargeable/hash/md5.hpp>
#include <cstdio>

void md5_print(const rechargeable::md5_digest& digest)
{
	for (std::size_t i = 0; i < 16; ++i)
		printf("%02x", digest.digest[i]);
}

void md5_test(const char* value)
{
	rechargeable::md5_digest test = rechargeable::md5::hash(value);
	printf("\nMD5 (\"%s\"): ", value);
	md5_print(test);
}

int main()
{
	md5_test("");
	md5_test("a");
	md5_test("abc");
	md5_test("message digest");
	md5_test("abcdefghijklmnopqrstuvwxyz");
	md5_test("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	md5_test("12345678901234567890123456789012345678901234567890123456789012345678901234567890");
}
