/**
 * \file const_char_wrapper.hpp
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

#ifndef RECHARGEABLE_DETAIL_CONST_CHAR_WRAPPER_HPP_INCLUDED
#define RECHARGEABLE_DETAIL_CONST_CHAR_WRAPPER_HPP_INCLUDED

#include <rechargeable/config.hpp>

namespace rechargeable { namespace detail
{
	class const_char_wrapper
	{
		public:

			const_char_wrapper(const char* str);

			const char* get_string() const;

		private:

			const char* _string;

	} ; // end class const_char_wrapper

	#include <rechargeable/hash/detail/const_char_wrapper.inl>

} } // end namespace rechargeable::detail

#endif // end RECHARGEABLE_DETAIL_CONST_CHAR_WRAPPER_HPP_INCLUDED
