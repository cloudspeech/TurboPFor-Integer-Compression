/**
    Copyright (C) powturbo 2013-2015
    GPL v2 License
  
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

    - homepage : https://sites.google.com/site/powturbo/
    - github   : https://github.com/powturbo
    - twitter  : https://twitter.com/powturbo
    - email    : powturbo [_AT_] gmail [_DOT_] com
**/
//     bitpack.c - "Integer Compression" bit packing 
  #ifndef IPPB
#include <stdio.h>
#include "bitpack.h" 
#define PAD8(__x) ( (((__x)+8-1)/8) )

#define IPPB( __ip,__x, __parm)
#define SRC( __ip,__x) (*__ip++)
#define SRC1(__ip,__x) (*(__ip))
#include __FILE__
 
unsigned char *bitpack32(unsigned       *__restrict in, unsigned n, unsigned char *__restrict out, unsigned nb) { unsigned char *pout = out+PAD8(n*nb); BITPACK32(in, n, nb, out, 0); return pout; } 
unsigned char *bitpack16(unsigned short *__restrict in, unsigned n, unsigned char *__restrict out, unsigned nb) { unsigned char *pout = out+PAD8(n*nb); BITPACK32(in, n, nb, out, 0); return pout; }
#undef IPPB 
#undef SRC
#undef SRC1

#define IPPB( __ip,__x, __parm) as = *__ip-start; start=*__ip++
#define SRC( __ip,__x) as
#define SRC1(__ip,__x) (*__ip - start)
#include __FILE__

unsigned char *bitdpack32(unsigned       *__restrict in, unsigned n, unsigned char *__restrict out, unsigned start, unsigned nb) { unsigned char *pout = out+PAD8(n*nb); unsigned as; BITPACK32(in, n, nb, out, start); return pout; } 
#undef IPPB
#undef SRC1

#define IPPB( __ip,__x, __parm) as = *__ip-start-1; start=*__ip++
#define SRC1(__ip,__x) (*__ip - start-1)
#include __FILE__
unsigned char *bitd1pack32(unsigned       *__restrict in, unsigned n, unsigned char *__restrict out, unsigned start, unsigned nb) { unsigned char *pout = out+PAD8(n*nb); unsigned as; BITPACK32(in, n, nb, out, start); return pout; } 
//-----------------------------------------------------------------------------------------------
  #else
#include <stdint.h>
#define USE_BITPACK 64
#define SRCI(__ip)

  #if USE_BITPACK == 64
#include "bitpack64_.h"
#define BITPACK32(__ip, __n, __nbits, __op, __parm) { typeof(__ip[0]) *_ipe=(__ip)+(__n);/*((__n+31)&0xffffffe0u)*/;\
  switch(__nbits) {\
    case  0:__ip = _ipe; break;\
    case  1:do BITPACK64_1( __ip, __op, __parm) while(__ip < _ipe); break;\
    case  2:do BITPACK64_2( __ip, __op, __parm) while(__ip < _ipe); break;\
    case  3:do BITPACK64_3( __ip, __op, __parm) while(__ip < _ipe); break;\
    case  4:do BITPACK64_4( __ip, __op, __parm) while(__ip < _ipe); break;\
    case  5:do BITPACK64_5( __ip, __op, __parm) while(__ip < _ipe); break;\
    case  6:do BITPACK64_6( __ip, __op, __parm) while(__ip < _ipe); break;\
    case  7:do BITPACK64_7( __ip, __op, __parm) while(__ip < _ipe); break;\
    case  8:do BITPACK64_8( __ip, __op, __parm) while(__ip < _ipe); break;\
    case  9:do BITPACK64_9( __ip, __op, __parm) while(__ip < _ipe); break;\
    case 10:do BITPACK64_10(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 11:do BITPACK64_11(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 12:do BITPACK64_12(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 13:do BITPACK64_13(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 14:do BITPACK64_14(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 15:do BITPACK64_15(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 16:do BITPACK64_16(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 17:do BITPACK64_17(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 18:do BITPACK64_18(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 19:do BITPACK64_19(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 20:do BITPACK64_20(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 21:do BITPACK64_21(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 22:do BITPACK64_22(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 23:do BITPACK64_23(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 24:do BITPACK64_24(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 25:do BITPACK64_25(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 26:do BITPACK64_26(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 27:do BITPACK64_27(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 28:do BITPACK64_28(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 29:do BITPACK64_29(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 30:do BITPACK64_30(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 31:do BITPACK64_31(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 32:do BITPACK64_32(__ip, __op, __parm) while(__ip < _ipe);\
  }\
}
  #else
#include "bitpack32_.h" // Not included in the github package
#define BITPACK32(__ip, __n, __nbits, __op, __parm) do { typeof(__ip[0]) *_ipe=(__ip)+(__n);/*((__n+31)&0xffffffe0u)*/;\
  switch(__nbits) {\
    case  0:__ip = _ipe; break;\
    case  1:do BITPACK32_1( __ip, __op, __parm) while(__ip < _ipe); break;\
    case  2:do BITPACK32_2( __ip, __op, __parm) while(__ip < _ipe); break;\
    case  3:do BITPACK32_3( __ip, __op, __parm) while(__ip < _ipe); break;\
    case  4:do BITPACK32_4( __ip, __op, __parm) while(__ip < _ipe); break;\
    case  5:do BITPACK32_5( __ip, __op, __parm) while(__ip < _ipe); break;\
    case  6:do BITPACK32_6( __ip, __op, __parm) while(__ip < _ipe); break;\
    case  7:do BITPACK32_7( __ip, __op, __parm) while(__ip < _ipe); break;\
    case  8:do BITPACK32_8( __ip, __op, __parm) while(__ip < _ipe); break;\
    case  9:do BITPACK32_9( __ip, __op, __parm) while(__ip < _ipe); break;\
    case 10:do BITPACK32_10(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 11:do BITPACK32_11(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 12:do BITPACK32_12(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 13:do BITPACK32_13(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 14:do BITPACK32_14(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 15:do BITPACK32_15(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 16:do BITPACK32_16(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 17:do BITPACK32_17(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 18:do BITPACK32_18(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 19:do BITPACK32_19(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 20:do BITPACK32_20(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 21:do BITPACK32_21(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 22:do BITPACK32_22(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 23:do BITPACK32_23(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 24:do BITPACK32_24(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 25:do BITPACK32_25(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 26:do BITPACK32_26(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 27:do BITPACK32_27(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 28:do BITPACK32_28(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 29:do BITPACK32_29(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 30:do BITPACK32_30(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 31:do BITPACK32_31(__ip, __op, __parm) while(__ip < _ipe); break;\
    case 32:do BITPACK32_32(__ip, __op, __parm) while(__ip < _ipe);\
  }\
} while(0)
  #endif
  #endif
