/*
 * Copyright (c) 1980, 1991, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 * Copyright (c) 2020 Dylan Lom <djl@dylanlom.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SECSPERMIN (time_t)60
#define SECSPERHOUR (time_t)3600
#define SECSPERDAY (time_t)86400

int main(int argc, char *argv[]){
	char mode;
	int opt;
	if (argc < 2){
		mode='s';
	} else {
		while ((opt = getopt(argc, argv, "smHdh")) != -1) {
			switch(opt){
				case 's': mode='s'; break;
				case 'm': mode='m'; break;
				case 'H': mode='H'; break;
				case 'd': mode='d'; break;
				case 'h': printf("%s [-s|-m|-H|-d][-h]\n", argv[0]); exit(0); break;
				default: fprintf(stderr, "%s [-s|-m|-H|-d][-h]\n", argv[0]); exit(1); break;
			}
		}
	}


	struct timespec boottime;
	time_t uptime;
	int mins, hrs, days;

	if (clock_gettime(CLOCK_BOOTTIME, &boottime) != -1){
		uptime = boottime.tv_sec;
		if (uptime < 60)
			uptime += 60;
		mins = uptime / SECSPERMIN;
		hrs = uptime / SECSPERHOUR;
		days = uptime / SECSPERDAY;

		switch(mode) {
			case 's': printf("%d\n", (int)uptime); break;
			case 'm': printf("%d\n", (int)mins); break;
			case 'H': printf("%d\n", (int)hrs); break;
			case 'd': printf("%d\n", (int)days); break;
		}
	}
}
