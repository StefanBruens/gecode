/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Guido Tack <tack@gecode.org>
 *
 *  Copyright:
 *     Guido Tack, 2007
 *
 *  Last modified:
 *     $Date: 2007-08-09 15:30:21 +0200 (Thu, 09 Aug 2007) $ by $Author: tack $
 *     $Revision: 4790 $
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef __GECODE_SUPPORT_STRING_HH__
#define __GECODE_SUPPORT_STRING_HH__

#include "gecode/kernel.hh"
#include <iostream>

namespace Gecode { namespace Support {
  
  /** \brief Immutable strings
    *
    */
  class String {
  private:
    
    /** \brief Reference-counted string objects
      *
      */
    class SO {
    public:
      /// The reference count
      unsigned int use_cnt;
      /// Reference counting: cancel subscription
      bool cancel(void);
      /// Reference counting: subscribe to an SO
      void subscribe(void);

      union {
        const char* c; ///< Used if the SO does not own the string
        char* o;       ///< Used if the SO owns the string
      } s;
      /// Whether the SO owns the string
      bool own;
      /// Left branch of a string tree, or NULL if the SO has an actual string
      SO* left;
      /// Right branch of a string tree
      SO* right;

      /// Construct from a given string \a s0, which is copied if \a copy is true.
      SO(const char* s0, bool copy);
      /// Construct an SO representing the concatenation of \a l and \a r
      SO(SO* l, SO* r);
      /// Destructor
      ~SO(void);
      /// Compare with \a other
      int cmp(SO* other) const;
      /// Return size of the string
      unsigned int size(void) const;
      /// Output to \a os
      std::ostream& print(std::ostream& os) const;
      /// Copy this string into \a to starting at position \a i
      int fill(char* to, int i) const;
      /// Return a newly allocated copy of this string
      char* c_str() const;
    };
    
    /** \brief Character-wise iterator for string objects
      *
      */
    class SOIter {
    private:
      /// Iterate left subtree
      SOIter* left;
      /// Iterate right subtree
      SOIter* right;
      /// Iterate string object
      const SO* so;
      /// Size of string to iterate
      int size;
      /// Current position of iteration
      int n;
    public:
      /// Constructor
      SOIter(const SO* so);
      /// Destructor
      ~SOIter(void);
      /// Test if iterator is still at a valid position
      bool operator()(void);
      /// Advance iterator to next position
      void operator++(void);
      /// Return character at current iterator position
      char c(void) const;
    };

    /// The string object
    SO* so;
  public:
    /// Construct empty string
    String(void);
    /// Construct string from \a s0, make a copy if \a copy is true.
    String(const char* s0, bool copy = false);
    /// Destructor
    ~String(void);
    /// Copy constructor
    String(const String& s0);
    /// Assignment operator
    const String& operator=(const String& s0);
    
    /// Compare with \a s0
    int cmp(const String& s0) const;
    /// Test if this string is equal to \a s0
    bool operator==(const String& s0) const;
    /// Return if string is empty
    bool empty(void) const;
    
    /// Return concatenation with \a s0
    String operator+(const String& s0) const;
    /// Print this string to \a os
    std::ostream& print(std::ostream& os) const;    
  };

  /** \brief Comparison for string objects
    */
  class StringCmp {
  public:
    /// Compare \a s0 with \a s1
    int cmp(const String& s0, const String& s1);
  };

  forceinline
  String::SO::SO(const char* s0, bool copy)
  : own(copy), left(NULL), right(NULL) {
    if (own) {
      int size = strlen(s0);
      s.o = static_cast<char*>(Memory::malloc(sizeof(char*)*(size+1)));
      memcpy(s.o, s0, size);
      s.o[size] = 0;
    } else {
      s.c = s0;
    }
  }

  forceinline bool
  String::SO::cancel(void) { return --use_cnt == 0; }

  forceinline void
  String::SO::subscribe(void) { ++use_cnt; }

  forceinline
  String::SO::SO(SO* l, SO* r) : own(false), left(l), right(r) {
    s.c = NULL; assert(l != NULL); assert(r != NULL);
    left->subscribe(); right->subscribe();
  }

  forceinline
  String::SO::~SO(void) {
    if (own)
      Memory::free(s.o);
    if (left && left->cancel())
      delete left;
    if (right && right->cancel())
      delete right;
  }

  forceinline unsigned int
  String::SO::size(void) const {
    if (s.c)
      return strlen(s.c);
    if (!left)
      return 0;
    return left->size() + right->size();
  }

  forceinline std::ostream&
  String::SO::print(std::ostream& os) const {
    if (s.c) {
      return os << s.c;
    }
    if (left) {
      return right->print(left->print(os));
    }
    return os;
  }

  forceinline int
  String::SO::fill(char* to, int i) const {
    if (s.c) {
      int l = strlen(s.c);
      memcpy(to+i, s.c, l);
      return i+l;
    }
    if (!left)
      return i;
    int l = left->fill(to, i);
    return right->fill(to, l);
  }

  forceinline char*
  String::SO::c_str() const {
    int s = size();
    char* ret = 
      static_cast<char*>(Memory::malloc(sizeof(char)*(s+1)));
    (void) fill(ret, 0);
    ret[s] = 0;
    return ret;
  }

  forceinline
  String::String(void) : so(NULL) {}

  forceinline
  String::String(const char* s0, bool copy) {
    so = new SO(s0, copy);
    so->subscribe();
  }

  forceinline
  String::~String(void) {
    if (so && so->cancel())
      delete so;
  }

  forceinline
  String::String(const String& s0) {
    so = s0.so;
    if (so)
      so->subscribe();
  }

  forceinline const String&
  String::operator=(const String& s0) {
    if (this != &s0) {
      if (so && so->cancel())
        delete so;
      so = s0.so;
      if (so)
        so->subscribe();
    }
    return *this;
  }
  
  forceinline bool
  String::empty(void) const {
    return so==NULL;
  }
  
  forceinline String
  String::operator+(const String& s0) const {
    String ret;
    if (so == NULL) {
      ret.so = s0.so;
      if (ret.so)
        ret.so->subscribe();
      return ret;
    }
    if (s0.so == NULL) {
      ret.so = so;
      ret.so->subscribe();
      return ret;
    }
    ret.so = new SO(so, s0.so);
    ret.so->subscribe();
    return ret;
  }
  
  forceinline bool
  String::operator==(const String& s0) const {
    if (so == NULL)
      return (s0.so == NULL);
    return so->cmp(s0.so)==0;
  }

  forceinline int
  String::cmp(const String& s0) const {
    if (so == NULL)
      return (s0.so == NULL ? 0 : -1);
    return so->cmp(s0.so);
  }
  
  forceinline std::ostream&
  String::print(std::ostream& os) const {
    if (so) return so->print(os);
    return os;
  }

  forceinline
  String::SOIter::SOIter(const String::SO* so0) : n(0) {
    if (so0->s.c) {
      so = so0; size = strlen(so->s.c); left = NULL; right = NULL;
    } else {
      so = NULL;
      left  = new SOIter(so0->left);
      right = new SOIter(so0->right);
    }
  }
  forceinline
  String::SOIter::~SOIter(void) {
    if (left)  delete left;
    if (right) delete right;
  }
  forceinline bool
  String::SOIter::operator()(void) {
    if (so)
      return n < size;
    return (*left)() || (*right)();
  }
  forceinline void
  String::SOIter::operator++(void) {
    if (so) {
      n++;
      return;
    }
    if ((*left)()) {
      ++(*left);
      return;
    }
    ++(*right);
  }
  forceinline char
  String::SOIter::c(void) const {
    if (so)
      return so->s.c[n];
    if ((*left)())
      return left->c();
    return right->c();
  }

  forceinline
  int
  String::SO::cmp(SO* other) const {
    if (s.c && other->s.c)
      return (s.c==other->s.c ? 0 : strcmp(s.c,other->s.c));
    SOIter me(this); SOIter notme(other);
    for (; me() && notme(); ++me, ++notme)
      if (me.c() != notme.c())
        return me.c() < notme.c() ? -1 : 1;
    if (me())
      return -1;
    if (notme())
      return 1;
    return 0;
  }

  forceinline int
  StringCmp::cmp(const String& s0, const String& s1) {
    return s0.cmp(s1);
  }
  
}}

forceinline
std::ostream&
operator<<(std::ostream& os, const Gecode::Support::String& x) {
  return x.print(os);
}

#endif

// STATISTICS: support-any
