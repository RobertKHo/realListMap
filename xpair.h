// $Id: xpair.h,v 1.1 2015-02-12 11:22:36-08 - - $
//Robert Ho rokho@ucsc.edu
//Daniel Urrutia deurruti@ucsc.edu
#ifndef __XPAIR_H__
#define __XPAIR_H__

#include <iostream>

using namespace std;

//
// Class xpair works like pair(c++).
//
// The implicitly generated members will work, because they just
// send messages to the first and second fields, respectively.
// Caution:  xpair() does not initialize its fields unless
// First and Second do so with their default ctors.
//

template <typename First, typename Second>
struct xpair {
   First first{};
   Second second{};
   xpair(){}
   xpair (const First& first, const Second& second):
               first(first), second(second) {}
};

template <typename First, typename Second>
ostream& operator<< (ostream& out, const xpair<First,Second>& pair) {
   out << "{" << pair.first << "," << pair.second << "}";
   return out;
}

#endif

