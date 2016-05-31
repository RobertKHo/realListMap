// $Id: xless.h,v 1.1 2015-02-12 11:22:36-08 - - $
//Robert Ho rokho@ucsc.edu
//Daniel Urrutia deurruti@ucsc.edu
#ifndef __XLESS_H__
#define __XLESS_H__

//
// We assume that the type type_t has an operator< function.
//

template <typename Type>
struct xless {
   bool operator() (const Type& left, const Type& right) const {
      return left < right;
   }
};

#endif

