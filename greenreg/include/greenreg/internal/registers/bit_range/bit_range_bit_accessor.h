/*
Copyright (c) 2008, Intel Corporation
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.
    * Neither the name of Intel Corporation nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// ChangeLog GreenSocs
// 2009-01-21 Christian Schroeder: changed namespace
// 2009-01-29 Christian Schroeder: renamings
// 2009-01-29 FURTHER CHANGES SEE SVN LOG!


#ifndef BIT_RANGE_BIT_ACCESSOR_H_
#define BIT_RANGE_BIT_ACCESSOR_H_

#include "greenreg/gr_externs.h"

namespace gs {
namespace reg {

class bit_accessor;
class bit;

////////////////////////////////////////////
/// bit_range_bit_accessor
/// This could be considered the user accessability class
/// to bits.  It serves as one of two possible access
/// methodologies to the bits (the other bieng the bit_accessor
/// which does all the real work.
/// @author 
/// @since 
////////////////////////////////////////////
class bit_range_bit_accessor
{
public:
	////////////////////////////////////////////
	/// Constructor
	///
	/// @param _b ? real bit accessor
	/// @param _start_bit ? bit this bit range starts on
	///
	/// @see I_register
	////////////////////////////////////////////
	bit_range_bit_accessor( bit_accessor & _b, gr_uint_t _start_bit);

	////////////////////////////////////////////
	/// Destructor
	////////////////////////////////////////////
	virtual ~bit_range_bit_accessor();

	////////////////////////////////////////////
	/// operator []
	/// accessability operator for bits.
	/// NOTE: this operator starts from the bit ranges start bit
	///
	/// @param _bit_id ? bit number
	/// @return reference to bit if valid, error message and dummy bit otherwise
	///
	/// @see bit
	////////////////////////////////////////////
	bit & operator [] ( gr_uint_t _bit_id);

protected:

	/// reference to the real bit accessor
	bit_accessor * b;

	/// starting bit of the bit range
	gr_uint_t m_start_bit;
};

} // end namespace gs:reg
} // end namespace gs:reg

#endif /*BIT_RANGE_BIT_ACCESSOR_H_*/
