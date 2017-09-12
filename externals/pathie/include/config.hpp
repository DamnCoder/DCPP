/* -*- coding: utf-8 -*-
 * This file is part of Pathie.
 *
 * Pathie is a path management library.
 * Copyright © 2015 Marvin Gülker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PATHIE_CONFIG_HPP
#define PATHIE_CONFIG_HPP

#define PATHIE_VERSION_MAJOR "0"
#define PATHIE_VERSION_MINOR "0"
#define PATHIE_VERSION_PATCH "1"
#define PATHIE_VERSION_GIT "cc4d296"

// Compiler chaos. Compilers targetting MacOS for unknown reasons
// don’t set __unix__, although that’s a BSD derivative, and BSD
// *is* some kind of UNIX. BSD macro check here only for extra-sure,
// maybe some compilers don’t set it...
#if defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(BSD)
#define _PATHIE_UNIX
#endif

// Skip any checking of locale for path names and just assume everything
// is UTF-8 on UNIX systems. This flag has no effect on Win32.
/* #undef ASSUME_UTF8_ON_UNIX */

#endif
