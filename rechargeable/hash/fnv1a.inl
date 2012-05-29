/**
 * \file config.hpp
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

#ifndef RECHARGEABLE_FNV1A_INL_INCLUDED
#define RECHARGEABLE_FNV1A_INL_INCLUDED

//---------------------------------------------------------------------

RECHARGEABLE_FORCE_INLINE
void initialize_context(fnv1a_context* context)
{
	context->value = fnv1a_context::offset;
}

//---------------------------------------------------------------------

RECHARGEABLE_FORCE_INLINE
fnv1a_context::hash_value finalize_context(fnv1a_context* context)
{
	return context->value;
}

//---------------------------------------------------------------------

template <std::size_t N>
RECHARGEABLE_FORCE_INLINE
fnv1a::hash_value fnv1a::hash(const char (&buffer)[N])
{
	return (hash<N-1>((const char(&)[N-1])buffer) ^ buffer[N-1]) * fnv1a_context::prime;
}

//---------------------------------------------------------------------

template <>
RECHARGEABLE_FORCE_INLINE
fnv1a::hash_value fnv1a::hash<1>(const char (&buffer)[1])
{
	return (fnv1a_context::offset ^ buffer[0]) * fnv1a_context::prime;
}

//---------------------------------------------------------------------

RECHARGEABLE_FORCE_INLINE
fnv1a::hash_value fnv1a::hash(const char* buffer)
{
	fnv1a_context context;
	initialize_context(&context);

	while (*buffer != '\0')
	{
		context.value ^= *buffer++;
		context.value *= fnv1a_context::prime;
	}

	return finalize_context(&context);
}

//---------------------------------------------------------------------

RECHARGEABLE_FORCE_INLINE
void fnv1a::hash(const char* buffer, std::size_t count, fnv1a_context* context)
{
	for (std::size_t i = 0; i < count; ++i)
	{
		context->value ^= *buffer++;
		context->value *= fnv1a_context::prime;
	}
}

#endif // end RECHARGEABLE_FNV1A_INL_INCLUDED
