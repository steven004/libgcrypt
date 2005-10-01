/* mpi-cmp.c  -  MPI functions
 * Copyright (C) 1998, 1999, 2001, 2002, 2005 Free Software Foundation, Inc.
 *
 * This file is part of Libgcrypt.
 *
 * Libgcrypt is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * Libgcrypt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#include <gcrypt-mpi-internal.h>
#include <stdlib.h>
#include <stdio.h>



int
_gcry_mpi_cmp_ui (gcry_core_context_t context, gcry_core_mpi_t u,
		       unsigned long v)
{
  mpi_limb_t limb = v;

  _gcry_mpi_normalize (u);
  if (!u->nlimbs && !limb)
    return 0;
  if (u->sign)
    return -1;
  if (u->nlimbs > 1)
    return 1;

  if (u->d[0] == limb)
    return 0;
  else if (u->d[0] > limb)
    return 1;
  else
    return -1;
}

int
_gcry_mpi_cmp (gcry_core_context_t context, gcry_core_mpi_t u,
		    gcry_core_mpi_t v)
{
  mpi_size_t usize, vsize;
  int cmp;

  _gcry_mpi_normalize (u);
  _gcry_mpi_normalize (v);
  usize = u->nlimbs;
  vsize = v->nlimbs;
  if (!u->sign && v->sign)
    return 1;
  if (u->sign && !v->sign)
    return -1;
  if (usize != vsize && !u->sign && !v->sign)
    return usize - vsize;
  if (usize != vsize && u->sign && v->sign)
    return vsize + usize;
  if (!usize)
    return 0;
  if (!(cmp = _gcry_mpih_cmp (u->d, v->d, usize)))
    return 0;
  if ((cmp < 0 ? 1 : 0) == (u->sign ? 1 : 0))
    return 1;
  return -1;
}

/* END. */