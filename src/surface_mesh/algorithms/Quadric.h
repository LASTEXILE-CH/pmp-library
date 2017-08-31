//=============================================================================
#pragma once
//=============================================================================

#include <surface_mesh/types.h>

//=============================================================================

namespace surface_mesh {

//=============================================================================

//! This class stores a quadric as a symmetrix 4x4 matrix. Used by the error
//! quadric mesh decimation algorithms.
class Quadric
{
public: // clang-format off

    //! construct quadric from upper triangle of symmetrix 4x4 matrix
    Quadric(double a, double b, double c, double d,
            double e, double f, double g,
            double h, double i,
            double j)
        : m_a(a), m_b(b), m_c(c), m_d(d),
          m_e(e), m_f(f), m_g(g),
          m_h(h), m_i(i),
          m_j(j)
    {}

    //! constructor quadric from given plane equation: ax+by+cz+d=0
    Quadric(double a=0.0, double b=0.0, double c=0.0, double d=0.0)
        :  m_a(a*a), m_b(a*b), m_c(a*c),  m_d(a*d),
           m_e(b*b), m_f(b*c), m_g(b*d),
           m_h(c*c), m_i(c*d),
           m_j(d*d)
    {}

    //! construct from point and normal specifying a plane
    Quadric(const Normal& n, const Point& p)
    {
        *this = Quadric(n[0], n[1], n[2], -dot(n,p));
    }

    //! set all matrix entries to zero
    void clear() { m_a = m_b = m_c = m_d = m_e = m_f = m_g = m_h = m_i = m_j = 0.0; }

    //! add given quadric to this quadric
    Quadric& operator+=(const Quadric& q)
    {
        m_a += q.m_a; m_b += q.m_b; m_c += q.m_c; m_d += q.m_d;
        m_e += q.m_e; m_f += q.m_f; m_g += q.m_g;
        m_h += q.m_h; m_i += q.m_i;
        m_j += q.m_j;
        return *this;
    }

    //! multiply quadric by a scalar
    Quadric& operator*=(double s)
    {
        m_a *= s; m_b *= s; m_c *= s;  m_d *= s;
        m_e *= s; m_f *= s; m_g *= s;
        m_h *= s; m_i *= s;
        m_j *= s;
        return *this;
    }

    //! evaluate quadric Q at position p by computing (p^T * Q * p)
    double operator()(const Point& p) const
    {
        const double x(p[0]), y(p[1]), z(p[2]);
        return m_a*x*x + 2.0*m_b*x*y + 2.0*m_c*x*z + 2.0*m_d*x
            +  m_e*y*y + 2.0*m_f*y*z + 2.0*m_g*y
            +  m_h*z*z + 2.0*m_i*z
            +  m_j;
    }

private:

    double m_a, m_b, m_c, m_d,
        m_e, m_f, m_g,
        m_h, m_i,
        m_j;
}; // clang-format on

//=============================================================================
} // namespace surface_mesh
//=============================================================================
