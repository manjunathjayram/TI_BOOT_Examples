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
/******************************************************************************
 * FILE PURPOSE: Simple binary byte swap
 ******************************************************************************
 * FILE NAME: byteswapbin.c
 *
 * DESCRIPTION: Creates a byte swapped copy of a file
 *
 ******************************************************************************/
#include <stdio.h>
#include <malloc.h>


int main (int argc, char *argv[])
{

  FILE *fil;
  unsigned char *cdat;
  unsigned char *rdat;
  unsigned int len;
  int i;


  if (argc != 3)  {
    fprintf (stderr, "usage: %s infile outfile\n", argv[0]);
    return (-1);
  }


  fil = fopen (argv[1], "rb");
  if (fil == NULL)  {
    fprintf (stderr, "%s: Failed to open input file %s\n", argv[0], argv[1]);
    return (-1);
  }

  fseek (fil, 0, SEEK_END);
  len = ftell (fil);
  fclose (fil);

  cdat = malloc (len * sizeof (unsigned char));
  if (cdat == NULL)  {
    fprintf (stderr, "%s: Failed to malloc %d bytes\n", argv[0], len);
    return (-1);
  }

  fil = fopen (argv[1], "rb");
  if (fil == NULL)  {
    fprintf (stderr, "%s: Failed to open input file %s\n", argv[0], argv[1]);
    return (-1);
  }

  fread (cdat, sizeof(unsigned char), len, fil);

  fclose (fil);

  rdat = malloc (len * sizeof(unsigned char));
  if (rdat == NULL)  {
    fprintf (stderr, "%s: Failed to malloc second array of %d bytes\n", argv[0], len);
    free (cdat);
    return (-1);
  }

  for (i = 0; i < len; i++)
    rdat[i] = cdat[len - 1 - i];

  fil = fopen (argv[2], "wb");
  if (fil == NULL)  {
    fprintf (stderr, "%s: Failed to open output file %s\n", argv[0], argv[2]);
    free (cdat);
    free (rdat);
    return (-1);
  }
  
  fwrite (rdat, sizeof(unsigned char), len, fil);
  fclose (fil);
  free (rdat);
  free (cdat);

  return (0);

}

  
  









