/*
    Copyright (C) 2010 William Hart

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include <gmp.h>
#include <stdlib.h>
#include "flint.h"
#include "ulong_extras.h"
#include "nmod_vec.h"

void _nmod_vec_scalar_addmul_nmod(mp_ptr res, mp_srcptr vec, 
				             slong len, mp_limb_t c, nmod_t mod)
{
    if (mod.norm >= FLINT_BITS/2) /* addmul will fit in a limb */
    {
        mpn_addmul_1(res, vec, len, c);
        _nmod_vec_reduce(res, res, len, mod);
    }
    else /* products may take two limbs */
    {
        slong i;
        for (i = 0; i < len; i++)
            NMOD_ADDMUL(res[i], vec[i], c, mod); /* hi already reduced mod n */
   }
}
