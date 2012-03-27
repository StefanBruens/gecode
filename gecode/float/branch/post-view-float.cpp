/*
 *  CAUTION:
 *    This file has been automatically generated. Do not edit,
 *    edit the specification file
 *      gecode/float/branch/post-view-float.bs
 *    instead.
 *
 *  This file contains generated code fragments which are
 *  copyrighted as follows:
 *
 *  Main author:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2008
 *
 *  The generated code fragments are part of Gecode, the generic
 *  constraint development environment:
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

#include <gecode/float/branch.hh>

namespace Gecode { namespace Float { namespace Branch {

  /// Create virtual view selector for tie-breaking
  void
  virtualize(Gecode::Home home, FloatVarBranch vars,
             const Gecode::VarBranchOptions& o_vars,
             Gecode::ViewSelVirtualBase<FloatView>*& v) {
    switch (vars) {
    case FLOAT_VAR_RND:
      v = new (home) ViewSelVirtual<ViewSelRnd<FloatView> >(home,o_vars);
      break;
    case FLOAT_VAR_MIN_MIN:
      v = new (home) ViewSelVirtual<ByMinMin>(home,o_vars);
      break;
    case FLOAT_VAR_MIN_MAX:
      v = new (home) ViewSelVirtual<ByMinMax>(home,o_vars);
      break;
    case FLOAT_VAR_MAX_MIN:
      v = new (home) ViewSelVirtual<ByMaxMin>(home,o_vars);
      break;
    case FLOAT_VAR_MAX_MAX:
      v = new (home) ViewSelVirtual<ByMaxMax>(home,o_vars);
      break;
    case FLOAT_VAR_WIDTH_MIN:
      v = new (home) ViewSelVirtual<ByWidthMin>(home,o_vars);
      break;
    case FLOAT_VAR_WIDTH_MAX:
      v = new (home) ViewSelVirtual<ByWidthMax>(home,o_vars);
      break;
    case FLOAT_VAR_DEGREE_MIN:
      v = new (home) ViewSelVirtual<ViewSelDegreeMin<FloatView> >(home,o_vars);
      break;
    case FLOAT_VAR_DEGREE_MAX:
      v = new (home) ViewSelVirtual<ViewSelDegreeMax<FloatView> >(home,o_vars);
      break;
    case FLOAT_VAR_AFC_MIN:
      v = new (home) ViewSelVirtual<ViewSelAfcMin<FloatView> >(home,o_vars);
      break;
    case FLOAT_VAR_AFC_MAX:
      v = new (home) ViewSelVirtual<ViewSelAfcMax<FloatView> >(home,o_vars);
      break;
    case FLOAT_VAR_WIDTH_DEGREE_MIN:
      v = new (home) ViewSelVirtual<ByWidthDegreeMin>(home,o_vars);
      break;
    case FLOAT_VAR_WIDTH_DEGREE_MAX:
      v = new (home) ViewSelVirtual<ByWidthDegreeMax>(home,o_vars);
      break;
    case FLOAT_VAR_WIDTH_AFC_MIN:
      v = new (home) ViewSelVirtual<ByWidthAfcMin>(home,o_vars);
      break;
    case FLOAT_VAR_WIDTH_AFC_MAX:
      v = new (home) ViewSelVirtual<ByWidthAfcMax>(home,o_vars);
      break;
    default:
      throw UnknownBranching("Float::branch");
    }
  }

}}}

namespace Gecode {

  void
  branch(Gecode::Home home, const FloatVarArgs& x,
         FloatVarBranch vars, FloatValBranch vals,
         const Gecode::VarBranchOptions& o_vars,
         const Gecode::ValBranchOptions& o_vals) {
    using namespace Gecode;
    using namespace Gecode::Float;
    using namespace Gecode::Float::Branch;


    if (home.failed()) return;
    if (o_vars.activity.initialized() &&
        (o_vars.activity.size() != x.size()))
      throw ActivityWrongArity("branch");
    ViewArray<FloatView> xv(home,x);
    switch (vars) {
    case FLOAT_VAR_NONE:
      {
        ViewSelNone<FloatView> v(home,o_vars);
        post(home,xv,v,vals,o_vals,o_vars.bf);
      }
      break;
    case FLOAT_VAR_RND:
      {
        ViewSelRnd<FloatView> v(home,o_vars);
        post(home,xv,v,vals,o_vals,o_vars.bf);
      }
      break;
    case FLOAT_VAR_MIN_MIN:
      {
        ByMinMin v(home,o_vars);
        post(home,xv,v,vals,o_vals,o_vars.bf);
      }
      break;
    case FLOAT_VAR_MIN_MAX:
      {
        ByMinMax v(home,o_vars);
        post(home,xv,v,vals,o_vals,o_vars.bf);
      }
      break;
    case FLOAT_VAR_MAX_MIN:
      {
        ByMaxMin v(home,o_vars);
        post(home,xv,v,vals,o_vals,o_vars.bf);
      }
      break;
    case FLOAT_VAR_MAX_MAX:
      {
        ByMaxMax v(home,o_vars);
        post(home,xv,v,vals,o_vals,o_vars.bf);
      }
      break;
    case FLOAT_VAR_WIDTH_MIN:
      {
        ByWidthMin v(home,o_vars);
        post(home,xv,v,vals,o_vals,o_vars.bf);
      }
      break;
    case FLOAT_VAR_WIDTH_MAX:
      {
        ByWidthMax v(home,o_vars);
        post(home,xv,v,vals,o_vals,o_vars.bf);
      }
      break;
    case FLOAT_VAR_DEGREE_MIN:
      {
        ViewSelDegreeMin<FloatView> v(home,o_vars);
        post(home,xv,v,vals,o_vals,o_vars.bf);
      }
      break;
    case FLOAT_VAR_DEGREE_MAX:
      {
        ViewSelDegreeMax<FloatView> v(home,o_vars);
        post(home,xv,v,vals,o_vals,o_vars.bf);
      }
      break;
    case FLOAT_VAR_AFC_MIN:
      {
        ViewSelAfcMin<FloatView> v(home,o_vars);
        post(home,xv,v,vals,o_vals,o_vars.bf);
      }
      break;
    case FLOAT_VAR_AFC_MAX:
      {
        ViewSelAfcMax<FloatView> v(home,o_vars);
        post(home,xv,v,vals,o_vals,o_vars.bf);
      }
      break;
    case FLOAT_VAR_WIDTH_DEGREE_MIN:
      {
        ByWidthDegreeMin v(home,o_vars);
        post(home,xv,v,vals,o_vals,o_vars.bf);
      }
      break;
    case FLOAT_VAR_WIDTH_DEGREE_MAX:
      {
        ByWidthDegreeMax v(home,o_vars);
        post(home,xv,v,vals,o_vals,o_vars.bf);
      }
      break;
    case FLOAT_VAR_WIDTH_AFC_MIN:
      {
        ByWidthAfcMin v(home,o_vars);
        post(home,xv,v,vals,o_vals,o_vars.bf);
      }
      break;
    case FLOAT_VAR_WIDTH_AFC_MAX:
      {
        ByWidthAfcMax v(home,o_vars);
        post(home,xv,v,vals,o_vals,o_vars.bf);
      }
      break;
    default:
      throw UnknownBranching("Float::branch");
    }
  }

  void
  branch(Gecode::Home home, const FloatVarArgs& x,
         const Gecode::TieBreakVarBranch<FloatVarBranch>& vars,
         FloatValBranch vals,
         const Gecode::TieBreakVarBranchOptions& o_vars,
         const Gecode::ValBranchOptions& o_vals) {
    using namespace Gecode;
    using namespace Gecode::Float;
    using namespace Gecode::Float::Branch;


    if (home.failed()) return;
    if ((vars.a == FLOAT_VAR_NONE) || (vars.a == FLOAT_VAR_RND) ||
        ((vars.b == FLOAT_VAR_NONE) && (vars.c == FLOAT_VAR_NONE) && (vars.d == FLOAT_VAR_NONE))) {
      branch(home,x,vars.a,vals,o_vars.a,o_vals);
      return;
    }
    if (o_vars.a.activity.initialized() &&
        (o_vars.a.activity.size() != x.size()))
      throw ActivityWrongArity("branch (option a)");
    if (o_vars.b.activity.initialized() &&
        (o_vars.b.activity.size() != x.size()))
      throw ActivityWrongArity("branch (option b)");
    if (o_vars.c.activity.initialized() &&
        (o_vars.c.activity.size() != x.size()))
      throw ActivityWrongArity("branch (option c)");
    if (o_vars.d.activity.initialized() &&
        (o_vars.d.activity.size() != x.size()))
      throw ActivityWrongArity("branch (option d)");
    ViewArray<FloatView> xv(home,x);
    Gecode::ViewSelVirtualBase<FloatView>* tb[3];
    int n=0;
    if (vars.b != FLOAT_VAR_NONE)
      virtualize(home,vars.b,o_vars.b,tb[n++]);
    if (vars.c != FLOAT_VAR_NONE)
      virtualize(home,vars.c,o_vars.c,tb[n++]);
    if (vars.d != FLOAT_VAR_NONE)
      virtualize(home,vars.d,o_vars.d,tb[n++]);
    assert(n > 0);
    ViewSelTieBreakDynamic<FloatView> vbcd(home,tb,n);
    switch (vars.a) {
    case FLOAT_VAR_MIN_MIN:
      {
        ByMinMin va(home,o_vars.a);
        ViewSelTieBreakStatic<ByMinMin,
          ViewSelTieBreakDynamic<FloatView> > v(home,va,vbcd);
        post(home,xv,v,vals,o_vals,o_vars.a.bf);
      }
      break;
    case FLOAT_VAR_MIN_MAX:
      {
        ByMinMax va(home,o_vars.a);
        ViewSelTieBreakStatic<ByMinMax,
          ViewSelTieBreakDynamic<FloatView> > v(home,va,vbcd);
        post(home,xv,v,vals,o_vals,o_vars.a.bf);
      }
      break;
    case FLOAT_VAR_MAX_MIN:
      {
        ByMaxMin va(home,o_vars.a);
        ViewSelTieBreakStatic<ByMaxMin,
          ViewSelTieBreakDynamic<FloatView> > v(home,va,vbcd);
        post(home,xv,v,vals,o_vals,o_vars.a.bf);
      }
      break;
    case FLOAT_VAR_MAX_MAX:
      {
        ByMaxMax va(home,o_vars.a);
        ViewSelTieBreakStatic<ByMaxMax,
          ViewSelTieBreakDynamic<FloatView> > v(home,va,vbcd);
        post(home,xv,v,vals,o_vals,o_vars.a.bf);
      }
      break;
    case FLOAT_VAR_WIDTH_MIN:
      {
        ByWidthMin va(home,o_vars.a);
        ViewSelTieBreakStatic<ByWidthMin,
          ViewSelTieBreakDynamic<FloatView> > v(home,va,vbcd);
        post(home,xv,v,vals,o_vals,o_vars.a.bf);
      }
      break;
    case FLOAT_VAR_WIDTH_MAX:
      {
        ByWidthMax va(home,o_vars.a);
        ViewSelTieBreakStatic<ByWidthMax,
          ViewSelTieBreakDynamic<FloatView> > v(home,va,vbcd);
        post(home,xv,v,vals,o_vals,o_vars.a.bf);
      }
      break;
    case FLOAT_VAR_DEGREE_MIN:
      {
        ViewSelDegreeMin<FloatView> va(home,o_vars.a);
        ViewSelTieBreakStatic<ViewSelDegreeMin<FloatView>,
          ViewSelTieBreakDynamic<FloatView> > v(home,va,vbcd);
        post(home,xv,v,vals,o_vals,o_vars.a.bf);
      }
      break;
    case FLOAT_VAR_DEGREE_MAX:
      {
        ViewSelDegreeMax<FloatView> va(home,o_vars.a);
        ViewSelTieBreakStatic<ViewSelDegreeMax<FloatView>,
          ViewSelTieBreakDynamic<FloatView> > v(home,va,vbcd);
        post(home,xv,v,vals,o_vals,o_vars.a.bf);
      }
      break;
    case FLOAT_VAR_AFC_MIN:
      {
        ViewSelAfcMin<FloatView> va(home,o_vars.a);
        ViewSelTieBreakStatic<ViewSelAfcMin<FloatView>,
          ViewSelTieBreakDynamic<FloatView> > v(home,va,vbcd);
        post(home,xv,v,vals,o_vals,o_vars.a.bf);
      }
      break;
    case FLOAT_VAR_AFC_MAX:
      {
        ViewSelAfcMax<FloatView> va(home,o_vars.a);
        ViewSelTieBreakStatic<ViewSelAfcMax<FloatView>,
          ViewSelTieBreakDynamic<FloatView> > v(home,va,vbcd);
        post(home,xv,v,vals,o_vals,o_vars.a.bf);
      }
      break;
    case FLOAT_VAR_WIDTH_DEGREE_MIN:
      {
        ByWidthDegreeMin va(home,o_vars.a);
        ViewSelTieBreakStatic<ByWidthDegreeMin,
          ViewSelTieBreakDynamic<FloatView> > v(home,va,vbcd);
        post(home,xv,v,vals,o_vals,o_vars.a.bf);
      }
      break;
    case FLOAT_VAR_WIDTH_DEGREE_MAX:
      {
        ByWidthDegreeMax va(home,o_vars.a);
        ViewSelTieBreakStatic<ByWidthDegreeMax,
          ViewSelTieBreakDynamic<FloatView> > v(home,va,vbcd);
        post(home,xv,v,vals,o_vals,o_vars.a.bf);
      }
      break;
    case FLOAT_VAR_WIDTH_AFC_MIN:
      {
        ByWidthAfcMin va(home,o_vars.a);
        ViewSelTieBreakStatic<ByWidthAfcMin,
          ViewSelTieBreakDynamic<FloatView> > v(home,va,vbcd);
        post(home,xv,v,vals,o_vals,o_vars.a.bf);
      }
      break;
    case FLOAT_VAR_WIDTH_AFC_MAX:
      {
        ByWidthAfcMax va(home,o_vars.a);
        ViewSelTieBreakStatic<ByWidthAfcMax,
          ViewSelTieBreakDynamic<FloatView> > v(home,va,vbcd);
        post(home,xv,v,vals,o_vals,o_vars.a.bf);
      }
      break;
    default:
      throw UnknownBranching("Float::branch");
    }
  }

}


// STATISTICS: float-branch

