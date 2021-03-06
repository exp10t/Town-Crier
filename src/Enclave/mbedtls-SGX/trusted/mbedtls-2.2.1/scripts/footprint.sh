#!/bin/sh
#
# Copyright (c) 2016-2017 by Cornell University.  All Rights Reserved.
#
# Permission to use the "TownCrier" software ("TownCrier"), officially
# docketed at the Center for Technology Licensing at Cornell University
# as D-7364, developed through research conducted at Cornell University,
# and its associated copyrights solely for educational, research and
# non-profit purposes without fee is hereby granted, provided that the
# user agrees as follows:
#
# The permission granted herein is solely for the purpose of compiling
# the TowCrier source code. No other rights to use TownCrier and its
# associated copyrights for any other purpose are granted herein,
# whether commercial or non-commercial.
#
# Those desiring to incorporate TownCrier software into commercial
# products or use TownCrier and its associated copyrights for commercial
# purposes must contact the Center for Technology Licensing at Cornell
# University at 395 Pine Tree Road, Suite 310, Ithaca, NY 14850; email:
# ctl-connect@cornell.edu; Tel: 607-254-4698; FAX: 607-254-5454 for a
# commercial license.
#
# IN NO EVENT SHALL CORNELL UNIVERSITY BE LIABLE TO ANY PARTY FOR
# DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES,
# INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF TOWNCRIER AND ITS
# ASSOCIATED COPYRIGHTS, EVEN IF CORNELL UNIVERSITY MAY HAVE BEEN
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# THE WORK PROVIDED HEREIN IS ON AN "AS IS" BASIS, AND CORNELL
# UNIVERSITY HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
# ENHANCEMENTS, OR MODIFICATIONS.  CORNELL UNIVERSITY MAKES NO
# REPRESENTATIONS AND EXTENDS NO WARRANTIES OF ANY KIND, EITHER IMPLIED
# OR EXPRESS, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, OR THAT THE USE
# OF TOWNCRIER AND ITS ASSOCIATED COPYRIGHTS WILL NOT INFRINGE ANY
# PATENT, TRADEMARK OR OTHER RIGHTS.
#
# TownCrier was developed with funding in part by the National Science
# Foundation (NSF grants CNS-1314857, CNS-1330599, CNS-1453634,
# CNS-1518765, CNS-1514261), a Packard Fellowship, a Sloan Fellowship,
# Google Faculty Research Awards, and a VMWare Research Award.
#
set -eu

CONFIG_H='include/mbedtls/config.h'

if [ -r $CONFIG_H ]; then :; else
    echo "$CONFIG_H not found" >&2
    echo "This script needs to be run from the root of" >&2
    echo "a git checkout or uncompressed tarball" >&2
    exit 1
fi

if grep -i cmake Makefile >/dev/null; then
    echo "Not compatible with CMake" >&2
    exit 1
fi

if which arm-none-eabi-gcc >/dev/null 2>&1; then :; else
    echo "You need the ARM-GCC toolchain in your path" >&2
    echo "See https://launchpad.net/gcc-arm-embedded/" >&2
    exit 1
fi

ARMGCC_FLAGS='-Os -march=armv7-m -mthumb'
OUTFILE='00-footprint-summary.txt'

log()
{
    echo "$@"
    echo "$@" >> "$OUTFILE"
}

doit()
{
    NAME="$1"
    FILE="$2"

    log ""
    log "$NAME ($FILE):"

    cp $CONFIG_H ${CONFIG_H}.bak
    if [ "$FILE" != $CONFIG_H ]; then
        cp "$FILE"  $CONFIG_H
    fi

    {
        scripts/config.pl unset MBEDTLS_NET_C || true
        scripts/config.pl unset MBEDTLS_TIMING_C || true
        scripts/config.pl unset MBEDTLS_FS_IO || true
    } >/dev/null 2>&1

    CC=arm-none-eabi-gcc AR=arm-none-eabi-ar LD=arm-none-eabi-ld \
        CFLAGS="$ARMGCC_FLAGS" make clean lib >/dev/null

    OUT="size-${NAME}.txt"
    arm-none-eabi-size -t library/libmbed*.a > "$OUT"
    log "$( head -n1 "$OUT" )"
    log "$( tail -n1 "$OUT" )"

    cp ${CONFIG_H}.bak $CONFIG_H
}

# truncate the file just this time
echo "(generated by $0)" > "$OUTFILE"
echo "" >> "$OUTFILE"

log "Footprint of standard configurations (minus net.c, timing.c, fs_io)"
log "for bare-metal ARM Cortex-M3/M4 microcontrollers."

VERSION_H="include/mbedtls/version.h"
MBEDTLS_VERSION=$( sed -n 's/.*VERSION_STRING *"\(.*\)"/\1/p' $VERSION_H )
if git rev-parse HEAD >/dev/null; then
    GIT_HEAD=$( git rev-parse HEAD | head -c 10 )
    GIT_VERSION=" (git head: $GIT_HEAD)"
else
    GIT_VERSION=""
fi

log ""
log "mbed TLS $MBEDTLS_VERSION$GIT_VERSION"
log "$( arm-none-eabi-gcc --version | head -n1 )"
log "CFLAGS=$ARMGCC_FLAGS"

# creates the yotta config
yotta/create-module.sh >/dev/null

doit default    include/mbedtls/config.h
doit yotta      yotta/module/mbedtls/config.h
doit thread     configs/config-thread.h
doit suite-b    configs/config-suite-b.h
doit psk        configs/config-ccm-psk-tls1_2.h

zip mbedtls-footprint.zip "$OUTFILE" size-*.txt >/dev/null
