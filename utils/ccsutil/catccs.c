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
/*****************************************************************************************
 * FILE PURPOSE: Catenate a set of ccs format files
 *****************************************************************************************
 * FILE NAME: catccs.c
 *
 * DESCRIPTION: Catenates a set of CCS data files
 *
 *  usage:  catccs file1 file2 [file3 [file4 [..]]] [-out outfile] [-addr address]
 *
 *****************************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include "ccsutil.h"


/******************************************************************************
 * FUNCTION PURPOSE: Open a file, read the data
 ******************************************************************************
 * DESCRIPTION: The input name is opened, the data is read and returned.
 ******************************************************************************/

unsigned int *getData (char *invok, char *fname, int *n, unsigned int *addr)
{
   FILE *fp;
   unsigned int *dat;

   fp = fopen (fname, "r");
   if (fp == NULL)  {
      fprintf (stderr, "%s: failed to open file %s\n", invok, fname);
      return (NULL);
   }

   dat = readCcsFile (fp, n, addr);
   if (dat == NULL)  {
      fprintf (stderr, "%s: Failed to read data file %s\n", invok, fname);
      return (NULL);
   }

   fclose (fp);

   return (dat);

}

unsigned int readUint (char *c)
{
    unsigned int x;

    if ((c[0] == '0') && (c[1] == 'x'))
        sscanf (&c[2], "%x", &x);
    else
        sscanf (c, "%d", &x);

    return (x);

}

int main (int argc, char *argv[])
{

   int i, j, p, nfiles;
   unsigned int *data1, *data2, *data3, addr, junk;
   int n1, n2, n3;
   FILE *fout;
   char **fnames;

   unsigned int faddr = 0;

   fout = stdout;

   /* There must be at least two files */
   if (argc < 3)  {
     fprintf (stderr, "usage: %s file1 file2 [file3 [file4 [...]]] [-out outfile] [-addr ccs_address]\n", argv[0]);
     return (-1);
   }

   /* Allocate more then is needed, just to be safe */
   fnames = malloc (argc * sizeof (char *));
   if (fnames == NULL)  {
     fprintf (stderr, "%s: malloc failed\n", argv[0]);
     return (-1);
   }

   /* Group the args into input files and an output file specification */
   for (i = 1, nfiles = 0; i < argc; i++)  {

      if (!strcmp (argv[i], "-out"))  {
         fout = fopen (argv[i+1], "w");
         if (fout == NULL)  {
            fprintf (stderr, "%s: Failed to open output file %s\n", argv[0], argv[i+1]);
            return (-1);
         } 
         i = i+ 1;

       }  else if (!strcmp (argv[i], "-addr"))  {

            faddr = readUint (argv[i+1]);
            i = i + 1;


       }  else  {

         fnames[nfiles++] = argv[i];

       }

    }


   /* Read the first data file */
   data1 = getData (argv[0], fnames[0], &n1, &addr);
   if (data1 == NULL) 
      return (-1);


   for (i = 1; i < nfiles; i++)  {

      data2 = getData (argv[0], fnames[i], &n2, &junk);
      if (data2 == NULL)
         return (-1);

         
      /* Catenate */
      n3 = n1 + n2;
      data3 = malloc (n3 * sizeof (unsigned int));
      if (data3 == NULL)  {
         fprintf (stderr, "%s: malloc failure on %d ints\n", argv[0], n3);
         return (-1);
      }

      for (j = p = 0; j < n1; j++, p++)
         data3[p] = data1[j];

      for (j = 0; j < n2; j++, p++)
         data3[p] = data2[j];

     free (data1);
     free (data2);
     data1 = data3;
     n1 = n3;

   }

   if (faddr != 0)
    addr = faddr;

   writeCcsFile (fout, data1, n1, addr);
   free (data1);
   free (fnames);

   if (fout != stdout)
     fclose (fout);

   return (0);

}

