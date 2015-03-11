/*
  Konvertuje binarni soubor na soubor *.c tak, aby po prelozeni se tento
  soubor stal soucasti vysledneho spustitelneho souboru. Je to zpusob jako
  do (zejmena) knihoven zabalit krome prelozitelnych zdrojovych kodu
  take i skripty, napriklad knihovnu v javascriptu. Ale lze to take pouzit
  pro vlozeni obrazku a jinych binarnich souboru, pokud to ma smysl

  Program vypisuje vysledny zdrojak na standardni vystup. Je mozne primo propojit s gcc

  bin2c soubor.dat nazev_souboru | gcc -c -o output.o -xc -Wall -Wno-trigraphs -

  vysledek bude v souboru output.o a vlastni soubor bude dostupny v promenne
	extern const char *nazev_souboru;

  a případně v
	extern unsigned int nazev_souboru_length;
  bude velikost


*/

#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv) {

if (argc != 3) {
	fputs("Converts binary file into compileable C file. \n"
		  "\n"
	     "The MIT License (MIT)\n"
	     "\n"
	     "Copyright (c) 2015 Ondrej Novak\n"
		 "\n"
		"Permission is hereby granted, free of charge, to any person obtaining a copy\n"
		"of this software and associated documentation files (the \"Software\"), to deal\n"
		"in the Software without restriction, including without limitation the rights\n"
		"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
		"copies of the Software, and to permit persons to whom the Software is\n"
		"furnished to do so, subject to the following conditions:\n"
		"\n"
		"The above copyright notice and this permission notice shall be included in all\n"
		"copies or substantial portions of the Software.\n"
		"\n"
		"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
		"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
		"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
		"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
		"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
		"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
		"SOFTWARE.\n"
		"\n"
		"Usage:\n"
		"        bin2c <file> <identifier>\n"
	     "\n"
	     "<file>       - source (binary) file. Use \"-\" to read standard input\n"
	     "<identifier> - name of global identifier that will be used to access\n"
	     "                the file from the code. It must be standrad C identifier.\n"
	     "                Program also creates <identifier>_length variable cointaining\n"
         "                length of the file in bytes\n"
		 "\n"
		 "Result is sent to the standard output\n"
	     "\n",stderr);
	return 1;
} else {
	FILE *f = strcmp(argv[1],"-")==0?stdin:fopen(argv[1],"rb");
        if (f == NULL) {
              fprintf(stderr,"Can't open input file '%s'", argv[1]);
              return errno;
        }
	printf("const char *%s=\"",argv[2]);
        int i = fgetc(f);
        int cnt = 0;
        unsigned int size = 0;
        while (i != -1) {
                size++;
		if (i >= 32 && i!='"' && i!='\\' && i < 128) {
			putchar(i); cnt++;
		} else if (i == '"') {
			putchar('\\'); putchar('"'); cnt+=2;
		} else if (i == '\\') {
			putchar('\\'); putchar('\\'); cnt+=2;
		} else if (i == '\n') {
			putchar('\\'); putchar('n'); cnt+=2;
		} else if (i == '\r') {
			putchar('\\'); putchar('r'); cnt+=2;
		} else if (i == '\t') {
			putchar('\\'); putchar('t'); cnt+=2;
		} else {
			printf("\\%03o",i); cnt +=4;
		}

		if (cnt >= 80) {
			printf("\"\n\"");
			cnt = 0;
		}
		i = fgetc(f);
	}
	fclose(f);
	printf("\";\n");
	printf("unsigned int %s_length=%u;\n",argv[2],size);
}


}
