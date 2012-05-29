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

#include <rechargeable/hash/fnv1a.hpp>
#include <cstdio>

int main()
{
	std::uint32_t compile_time = rechargeable::fnv1a::hash<5>("test");
	std::uint32_t run_time = rechargeable::fnv1a::hash("test");

	rechargeable::fnv1a_context context;
	initialize_context(&context);

	rechargeable::fnv1a::hash("test", 4, &context);

	std::uint32_t run_time_explicit = finalize_context(&context);
}
