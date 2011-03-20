/*================================================================================
 *
 * GeneralSerializer.hpp
 *
 * Author:
 *   Si Yin <zyzyis@gmail.com>
 *
 * Copyright (C) 2011 Hai Computing
 *
 * This file is released under the terms of the GNU General Public License
 * versions 3.0. Please refers to the file COPYING for more information.
 *================================================================================
 */

#ifndef SPLIT_T
#define SPLIT_T

struct Split {
	TRawData* binData;
	size_t* schema;
	size_t size;
};


#end