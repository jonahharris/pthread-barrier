#ifdef __APPLE__
/* ========================================================================= **
**           _   _                    _     _                  _             **
**      _ __| |_| |_  _ _ ___ __ _ __| |___| |__  __ _ _ _ _ _(_)___ _ _     **
**     | '_ \  _| ' \| '_/ -_) _` / _` |___| '_ \/ _` | '_| '_| / -_) '_|    **
**     | .__/\__|_||_|_| \___\__,_\__,_|   |_.__/\__,_|_| |_| |_\___|_|      **
**     |_|                                                                   **
**                                                                           **
** ========================================================================= **
**               POSIX THREAD BARRIER IMPLEMENTATION FOR OS X                **
** ========================================================================= **
**                                                                           **
** Portions Copyright (c) Brent Priddy                                       **
** Portions Copyright (c) Jonah H. Harris.                                   **
**                                                                           **
** This library is free software; you can redistribute it and/or modify it   **
** under the terms of the GNU Lesser General Public License as published by  **
** the Free Software Foundation; either version 3 of the License, or (at     **
** your option) any later version.                                           **
**                                                                           **
** This library is distributed in the hope it will be useful, but WITHOUT    **
** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or     **
** FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public       **
** License for more details.                                                 **
**                                                                           **
** You should have received a copy of the GNU Lesser General Public License  **
** along with this library; if not, write to the Free Software Foundation,   **
** Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                             **
** ========================================================================= */

/* ========================================================================= */
/* -- INCLUSIONS ----------------------------------------------------------- */
/* ========================================================================= */

#include "pthread_barrier.h"

/* ========================================================================= */
/* -- DEFINITIONS ---------------------------------------------------------- */
/* ========================================================================= */

/* ========================================================================= */
/* -- MACROS --------------------------------------------------------------- */
/* ========================================================================= */

/* ========================================================================= */
/* -- PRIVATE TYPES -------------------------------------------------------- */
/* ========================================================================= */

/* ========================================================================= */
/* -- PRIVATE METHOD PROTOTYPES -------------------------------------------- */
/* ========================================================================= */

/* ========================================================================= */
/* -- PRIVATE DATA --------------------------------------------------------- */
/* ========================================================================= */

/* ========================================================================= */
/* -- PUBLIC DATA ---------------------------------------------------------- */
/* ========================================================================= */

/* ========================================================================= */
/* -- EXTERNAL DATA -------------------------------------------------------- */
/* ========================================================================= */

/* ========================================================================= */
/* -- EXTERNAL FUNCTION PROTOTYPES ----------------------------------------- */
/* ========================================================================= */

/* ========================================================================= */
/* -- STATIC ASSERTIONS ---------------------------------------------------- */
/* ========================================================================= */

/* ========================================================================= */
/* -- PRIVATE METHODS ------------------------------------------------------ */
/* ========================================================================= */

/* ========================================================================= */
/* -- PUBLIC METHODS ------------------------------------------------------- */
/* ========================================================================= */

int
pthread_barrier_init (
  pthread_barrier_t            *barrier,
  const pthread_barrierattr_t  *attr,
  unsigned int count
) {
  if (0 == count) {
    errno = EINVAL;
    return -1;
  }

  if (0 > pthread_mutex_init(&barrier->mutex, 0)) {
    return -1;
  }

  if (0 > pthread_cond_init(&barrier->cond, 0)) {
    pthread_mutex_destroy(&barrier->mutex);
    return -1;
  }

  barrier->tripCount = count;
  barrier->count = 0;

  return 0;
} /* pthread_barrier_init() */

/* ------------------------------------------------------------------------- */

int
pthread_barrier_destroy (
  pthread_barrier_t            *barrier
) {
  pthread_cond_destroy(&barrier->cond);
  pthread_mutex_destroy(&barrier->mutex);
  return 0;
} /* pthread_barrier_destroy() */

/* ------------------------------------------------------------------------- */

int
pthread_barrier_wait (
  pthread_barrier_t            *barrier
) {
  pthread_mutex_lock(&barrier->mutex);
  ++(barrier->count);
  if (barrier->count >= barrier->tripCount) {
    barrier->count = 0;
    pthread_cond_broadcast(&barrier->cond);
    pthread_mutex_unlock(&barrier->mutex);
    return 1;
  } else {
    pthread_cond_wait(&barrier->cond, &(barrier->mutex));
    pthread_mutex_unlock(&barrier->mutex);
    return 0;
  }
} /* pthread_barrier_wait() */

#endif /* __APPLE__ */

/* :vi set ts=2 et sw=2: */

