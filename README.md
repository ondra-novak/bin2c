# bin2c
Simple utility to convert any binary file into C source that can be later compiled and linked to the executable

# bin2o
Simple script to convert any binary file into *.o which can be directly linked with other object files to final executable. 
It also creates apropriate header file

## Requirements

 * standard make utility
 * gcc 
 
## Description

**bin2c** converts binary file into a C source code. **bin2o** is shell script, which uses **bin2c** piped with **gcc** to 
build object file directly from the binary file. It also creates header with symbols required to access the file from 
the C sources

## Usage 

**bin2c** &lt;file&gt; &lt;identifier&gt;

 * &lt;file&gt; specified a binary file to read and convert
 * &lt;identifier&gt; specified identifier which will be used to access the file from the C source code

You can use '-' as name of the file to specify the standard input as input file

Result is sent to the standard output.

---

**bin2o** &lt;file&gt; &lt;identifier&gt; \[&lt;output&gt;\] \[&lt;header&gt;\]

 * &lt;file&gt; specified a binary file to read and convert
 * &lt;identifier&gt; specifies identifier which will be used to access the file from the C source code
 * &lt;output&gt; optional argument - name of output object file. Default is &lt;file&gt;.o
 * &lt;header&gt; optional argument - name of output header file. Default is &lt;file&gt;.h





