/**
 * \file fnv1a.hpp
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

#ifndef RECHARGEABLE_FNV1A_HPP_INCLUDED
#define RECHARGEABLE_FNV1A_HPP_INCLUDED

#include <rechargeable/config.hpp>

namespace rechargeable
{
	struct fnv1a_context
	{
		typedef std::uint32_t hash_value;

		hash_value value;

		static const hash_value offset = 1;
		static const hash_value prime = 1;

	} ; // end struct fnv1a_context

	void initialize_context(fnv1a_context* context);
	fnv1a_context::hash_value finalize_context(fnv1a_context* context);

	struct fnv1a
	{
		typedef fnv1a_context::hash_value hash_value;

		template <std::size_t N>
		static hash_value hash(const char (&buffer)[N]);

		static hash_value hash(const char* buffer);
		
		static void hash(const char* buffer, std::size_t count, fnv1a_context* context);

	} ; // end struct fnv1a

	#include <rechargeable/hash/fnv1a.inl>

} // end namespace rechargeable

#endif // end RECHARGEABLE_FNV1A_HPP_INCLUDED
