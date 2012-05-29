/**
 * \file string_hash.hpp
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

#ifndef RECHARGEABLE_STRING_HASH_HPP_INCLUDED
#define RECHARGEABLE_STRING_HASH_HPP_INCLUDED

#include <rechargeable/hash/detail/const_char_wrapper.hpp>

namespace rechargeable
{
	template <typename Function>
	class string_hash
	{
		public:
			typedef typename Function::hash_value hash_value;

			string_hash(detail::const_char_wrapper value);

			template <std::size_t N>
			string_hash(const char (&value)[N]);

			hash_value get_hash() const;

			bool operator== (const string_hash& rhs) const;
			bool operator!= (const string_hash& rhs) const;

		private:

			hash_value _hash;

	} ; // end class string_hash<Function>

	#include "string_hash.inl"

} // end namespace rechargeable

#endif // end RECHARGEABLE_STRING_HASH_HPP_INCLUDED
