/*
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/
/* Pad a ccs data file to a certain length. The length is in number of lines
 *
 *  usage: ccspad infile outfile pattern length 
 */

#include <stdio.h>
#include <malloc.h>
#include "ccsutil.h"

unsigned int readArg (char *a)
{
    unsigned int v;

    if ((a[0] == '0') && (a[1] == 'x'))
        sscanf (&a[2], "%x", &v);
    else
        sscanf (a, "%d", &v);

    return (v);

}


int main (int argc, char *argv[])
{
    unsigned int *data1, *data2;
    unsigned int  len1,   len2;
    unsigned int  pattern;
    unsigned int  i, addr;


    if (argc != 5)  {
        fprintf (stderr, "usage: %s infile outfile pattern length\n", argv[0]);
        return (-1);
    }


    pattern = readArg (argv[3]);
    len2    = readArg (argv[4]);

    data1 = openReadCloseCcsFile (argv[1], &len1, &addr);
    if (data1 == NULL)  {
        fprintf (stderr, "%s: Failed to open and read input file\n", argv[0]);
        return (-1);
    }

    if (len1 > len2) {
        fprintf (stderr, "Input file '%s' is bigger than the padded size. Skip this operation\n", argv[1]);
        free (data1);
        return (-1);
    }

    data2 = malloc (len2 * sizeof (unsigned int));
    if (data2 == NULL)  {
        fprintf (stderr, "%s: Malloc failed on %d unsigned ints\n", argv[0], len2);
        free (data1);
        return (-1);
    }

    for (i = 0; i < len1; i++)
        data2[i] = data1[i];

    for (  ; i < len2; i++)
        data2[i] = pattern;

    free (data1);

    openWriteCloseCcsFile (argv[2], data2, len2, addr);

    free (data2);

    return (0);

}
    


