// $Id: util.tcc,v 1.1 2015-02-12 11:22:36-08 - - $
//Robert Ho rokho@ucsc.edu
//Daniel Urrutia deurruti@ucsc.edu
#include <sstream>
#include <typeinfo>
using namespace std;

template <typename item_t>
ostream& operator<< (ostream& out, const list<item_t>& vec) {
   bool want_space = false;
   for (const auto& item: vec) {
      if (want_space) cout << " ";
      cout << item;
      want_space = true;
   }
   return out;
}

template <typename Type>
string to_string (const Type& that) {
   ostringstream stream;
   stream << that;
   return stream.str();
}

template <typename Type>
Type from_string (const string& that) {
   stringstream stream;
   stream << that;
   Type result;
   if (not (stream >> result and stream.eof())) {
      throw domain_error (string (typeid (Type).name())
            + " from_string (" + that + ")");
   }
   return result;
}

