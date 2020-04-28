/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2018 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _WESTEROS_UT_OPEN_H
#define _WESTEROS_UT_OPEN_H

#include <poll.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _SYS_IOCTL_H 1
#include <asm-generic/ioctl.h>

/* Hooks to allow brcm-em.cpp to intercept ioctl calls */
#define ioctl( d, r, p ) EMIOctl( (d), (r), (p) )

/* Hooks to allow brcm-em.cpp to intercept mmap calls */
#define mmap( addr, length, prot, flags, fd, offset ) EMMmap( addr, length, prot, flags, fd, offset)
#define munmap( addr, length ) EMMunmap( addr, length )

/* Hooks to allow brcm-em.cpp to intercept poll calls */
#define poll( pollfd, nfds, timeout ) EMPoll( pollfd, nfds, timeout )

/* Hooks to allow brcm-em.cpp to intercept stat calls */
#define stat( path, buf ) EMStat( (path), (buf) )

/* Hooks to allow brcm-em.cpp to intercept opendir,readdir,closdir calls */
#define opendir( name ) EMOpenDir( name )
#define readdir( dir ) EMReadDir( dir )
#define closedir( dir ) EMCloseDir( dir )

/* Hooks to allow brcm-em.cpp to intercept open calls */
#define GET_OPEN_MACRO(_1,_2,_3,NAME,...) NAME
#define open(...) GET_OPEN_MACRO(__VA_ARGS__, EMOpen3, EMOpen2)(__VA_ARGS__)
#define close(fd) EMClose(fd)
#define read( fd, buf, count ) EMRead( fd, buf, count )

int EMOpen2( const char *pathname, int flags );
int EMOpen3( const char *pathname, int flags, mode_t mode );
int EMClose( int fd );
ssize_t EMRead( int fd, void *buf, size_t count ) __wur;
int EMIOctl( int fd, int request, void *arg );
void *EMMmap( void *addr, size_t length, int prot, int flags, int fd, off_t offset ) __THROW;
int EMMunmap( void *addr, size_t length ) __THROW;
int EMPoll( struct pollfd *fds, nfds_t nfds, int timeout );
int EMStat(const char *path, struct stat *buf) __THROW;
DIR *EMOpenDir(const char *name);
int EMCloseDir(DIR *dirp);
struct dirent *EMReadDir(DIR *dirp);

#ifdef __cplusplus
}
#endif

#endif

