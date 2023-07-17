/* File Name: cmpl.h
 * PROGRAMMER: DB6
 * DATE: 21.07.2022
 */
#ifndef __cmpl_h_
#define __cmpl_h_

#include <cmath>

typedef double DBL;

/* Complex number representation type */
struct cmpl
{
  DBL Re, Im; // real and imaginary components

  cmpl ( DBL A, DBL B = 0) : Re(A), Im(B)
  {
  }

  ~cmpl( void )
  {
  }

  cmpl operator+( const cmpl &Z ) const
  {
    return cmpl(Re + Z.Re, Im + Z.Im);
  }

  cmpl operator+( const DBL &A ) const
  {
    return cmpl(Re + A, Im);
  }

  cmpl operator-( const cmpl &Z ) const
  {
    return cmpl(Re - Z.Re, Im - Z.Im);
  }

  cmpl operator-( const DBL &A ) const
  {
    return cmpl(Re - A, Im);
  }

  cmpl operator*( const cmpl &Z ) const
  {
    return cmpl(Re * Z.Re - Im * Z.Im, Re* Z.Im + Im * Z.Re);
  }

  cmpl operator*( const DBL &A ) const
  {
    return cmpl(Re * A, Im * A);
  }

  cmpl operator/( const cmpl &Z ) const
  {
    return cmpl((Re * Z.Re + Im * Z.Im) / (Z.Re * Z.Re + Z.Im * Z.Im), (Im * Z.Re + Re * Z.Im) / (Z.Re * Z.Re + Z.Im * Z.Im));
  }

  cmpl operator/( const DBL &A ) const
  {
    return cmpl(Re / A, Im / A);
  }

  DBL operator!( void ) const
  {
    return Re * Re + Im * Im;
  }

  cmpl operator-( void ) const
  {
    return cmpl(-Re, -Im);
  }

  cmpl operator&( int N ) const
  {
    cmpl Z(Re, Im);

    if (N <= 0)
      return cmpl(1);

    for (int i = 0; i < N; i++)
      Z = Z * Z;
    return Z;
  }

  cmpl Sin( void )
  {
    cmpl &Z = *this;
    return cmpl(1) - Z * Z / 2 + Z * Z * Z * Z / 24 - Z * Z * Z * Z * Z * Z / 720 + Z * Z * Z * Z * Z * Z * Z * Z / 40320;
  }

  cmpl Cos( void )
  {
    cmpl &Z = *this;
    return Z - Z * Z * Z / 6 + Z * Z * Z * Z * Z / 120 - Z * Z * Z * Z * Z * Z * Z / 5040 + Z * Z * Z * Z * Z * Z * Z * Z * Z / 362880;
  }

  /* Determing if complex number have zero in both components method.
   * ARGUMENTS: None;
   * RETURNS:
   *   (bool) true if there is zero.
   */
  bool HasZero( void )
  {
    return Re == 0 && Im == 0;
  } /* End of 'HasZero' method */

  /* Function for creating Newton fraktal.
   * ARGUMENTS:
   *   - link at complex number:
   *       const cmpl &Z;
   * RETURNS:
   *   (cmpl) expression result.
   */
  cmpl Func( const cmpl &Z )
  {
    return Z * Z * Z - 1;
  } /* End of 'Func' function */

  /* Function for creating Newton derivative fraktal.
   * ARGUMENTS:
   *   - link at complex number:
   *       const cmpl &Z;
   * RETURNS:
   *   (cmpl) expression result.
   */
  cmpl Deriv( const cmpl &Z )
  {
    return Z * Z * 3;
  } /* End of 'Deriv' function */

  /* Creating Newton fraktal method.
   * ARGUMENTS: None;
   * RETURNS:
   *   (int) iterations for get complex number count.
   */
  INT Newton( void )
  {
    int i = 0;
    cmpl &Z = *this;

    while (i < 255 && sqrt(!Z) < 2)
      Z = Z - Func(Z) * 1 / Deriv(Z), i++;
    return i;
  } /* End of 'Newton' method */
};

#endif // __cmpl_h_
/* END OF 'cmpl.h' FILE */
