/**
 * \file md5.hpp
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

#ifndef RECHARGEABLE_MD5_HPP_INCLUDED
#define RECHARGEABLE_MD5_HPP_INCLUDED

#include <rechargeable/hash/detail/const_char_wrapper.hpp>

namespace rechargeable
{
	class md5;

	struct md5_digest
	{
		std::uint8_t digest[16];

	} ; // end struct md5_digest

	bool operator== (const md5_digest& lhs, const md5_digest& rhs);
	bool operator!= (const md5_digest& lhs, const md5_digest& rhs);

	class md5_context
	{
		public:

			typedef md5_digest hash_value;

			md5_context();

			hash_value get_value();

		internal:

			friend class md5;
			
			std::uint32_t _count[2];
			std::uint32_t _state[4];
			std::uint8_t _buffer[64];

	} ; // end class md5_context

	class md5
	{
		public:
			typedef md5_context hash_context;
			typedef md5_context::hash_value hash_value;

			static hash_value hash(detail::const_char_wrapper str);
			static void hash(const char* buffer, std::size_t count, hash_context* context);

		private:

			md5() { }

	} ; // end struct md5

} // end namespace rechargeable

#endif // end RECHARGEABLE_MD5_HPP_INCLUDED
