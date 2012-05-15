/**
 * \file visual_cpp.hpp
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

#ifndef RECHARGEABLE_COMPILER_VISUAL_CPP_HPP_INCLUDED
#define RECHARGEABLE_COMPILER_VISUAL_CPP_HPP_INCLUDED

//---------------------------------------------------------------------
// Require a minimum version of Visual C++ Compiler
//
// The Rechargeable C++ Libraries requires at least Visual Studio 10
//---------------------------------------------------------------------

#if _MSC_VER < 1600
#	error "Unsupported version of Visual Studio. Requires 10 or later"
#endif

//---------------------------------------------------------------------
// Inlining macros
//---------------------------------------------------------------------

/**
 *
 */
#define RECHARGEABLE_INLINE inline

/**
 *
 */
#define RECHARGEABLE_FORCE_INLINE __forceinline

/**
 *
 */
#define RECHARGEABLE_NO_INLINE __declspec(noinline)

//---------------------------------------------------------------------
// DLL macros
//---------------------------------------------------------------------

/**
 *
 */
#define RECHARGEABLE_EXPORT __declspec(dllexport)

/**
 *
 */
#define RECHARGEABLE_IMPORT __declspec(dllimport)

#endif // end RECHARGEABLE_VISUAL_CPP_HPP_INCLUDED
