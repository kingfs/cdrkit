/*
 * This file has been modified for the cdrkit suite.
 *
 * The behaviour and appearence of the program code below can differ to a major
 * extent from the version distributed by the original author(s).
 *
 * For details, see Changelog file distributed with the cdrkit package. If you
 * received this file from another source then ask the distributing person for
 * a log of modifications.
 *
 */

/* @(#)sigdefs.h	1.5 02/01/19 Copyright 1997 J. Schilling */
/*
 *	Signal abstraction for BSD/SVR4 signals
 *
 *	Copyright (c) 1997 J. Schilling
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; see the file COPYING.  If not, write to the Free Software
 * Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef	_SIGDEFS_H
#define	_SIGDEFS_H

#ifndef _MCONFIG_H
#include <mconfig.h>
#endif

#ifdef	HAVE_SIGSET
/*
 * Try to by default use the function that sets up signal handlers in a way
 * that does not reset the handler after it has been called.
 */
#define	signal		sigset
#endif

#ifdef	HAVE_SIGPROCMASK
#define	block_sigs(a)	{ \
				sigset_t	__new;	\
							\
				sigfillset(&__new);	\
				sigprocmask(SIG_BLOCK, &__new, &a);\
			}
#define	unblock_sig(s)	{ \
				sigset_t	__new;	\
							\
				sigemptyset(&__new);	\
				sigaddset(&__new, (s));	\
				sigprocmask(SIG_UNBLOCK, &__new, NULL);\
			}
#define	restore_sigs(a)	sigprocmask(SIG_SETMASK, &a, 0);

#else	/* !HAVE_SIGPROCMASK */

#define	sigset_t	int
#define	block_sigs(a)	a = sigblock(0xFFFFFFFF)
#define	restore_sigs(a)	sigsetmask(a);
#define	unblock_sig(s)	{ \
				int	__old, __new;	\
							\
				block_sigs(__old);	\
				__new = sigmask(s);	\
				__new = __old & ~__new;	\
				sigsetmask(__new);	\
			}

#endif	/* HAVE_SIGPROCMASK */

#endif	/* _SIGDEFS_H */
