/**
 * \file config.hpp
 *
 * \section COPYRIGHT
 *
 * Rechargeable Battery Libraries
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

#ifndef RECHARGEABLE_CONFIG_HPP_INCLUDED
#define RECHARGEABLE_CONFIG_HPP_INCLUDED

//---------------------------------------------------------------------
// Determine compiler settings.
//---------------------------------------------------------------------

#include <rechargeable/config/select_compiler_config.hpp>

//---------------------------------------------------------------------
// Determine platform settings.
//---------------------------------------------------------------------

#include <rechargeable/config/select_platform_config.hpp>

//---------------------------------------------------------------------
// Include stddef for std::size_t.
//---------------------------------------------------------------------

#include <cstddef>

//---------------------------------------------------------------------
// Include stdint for various int sizes.
//
// Using stdint defines ensures that the size of an integer is
// consistent across platforms.
//---------------------------------------------------------------------

#include <cstdint>

//---------------------------------------------------------------------
// Specify items to export/import from a DLL.
//---------------------------------------------------------------------

#if defined(BUILDING_RECHARGEABLE_LIBRARIES)
#	define RECHARGEABLE_ITEM RECHARGEABLE_EXPORT
#else
#	define RECHARGEABLE_ITEM RECHARGEABLE_IMPORT
#endif

//---------------------------------------------------------------------
// Define internal.
//
// C# has an additional access control level called internal. The
// access level allows components in the same assembly to access the
// method or variable. The closest C++ analog is friendship.
//
// The intent of internal is to allow the library to denote certain
// member methods and variables as off limits. By default internal
// expands to private. Access is then granted through friendship.
//
// This behavior can be overriden by defining INTERNAL_IS_PUBLIC,
// which expands internal to public.
//---------------------------------------------------------------------

#define INTERNAL_IS_PUBLIC

#if defined(INTERNAL_IS_PUBLIC)
#	define internal public
#else
#	define internal private
#endif

#endif // end RECHARGEABLE_CONFIG_HPP_INCLUDED
