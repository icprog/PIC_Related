YOU MUST AGREE THIS TERMS AND CONDITIONS. THIS SOFTWARE IS
PROVIDED BY NORITAKE CO., INC "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR SORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------
ABOUT THIS LIBRARY
The Noritake_VFD_CUU code library provides methods to access the
base functionality of the CU-U Noritake Vacuum Fluorescent
Display (VFD) modules.

Noritake_VFD_CUU code library is appliacable to the CU-U VFD
modules with the following suffix.
	1) CU******-UW**
	2) CU******-UX**

	Example: CU20025-UW1J
	
Following CU-U VFD module cannot be used with the
Noritake_VFD_CUU code library.
	1) CU40045-UW1J	 

Noritake_VFD_CUU code library is optimized for use with Atmel
based chipsets.

This code library is configurable so that you may define the
interface it will use: serial, M68 parallel, or I80 parallel.

Please refer to configuration.txt for instructions on how to
set up the configuration. Also included is a working
configuration file, config.h.

----------------------------------------------------------------
ORGANIZATION
The code library is organized so that you can share a one copy of
the source code among projects and libraries that use it. The
top directory should contain the folders for the libraries
and your projects that use them. The code library's source and
header files are contained in the src directory. The
documentation is contained in the doc directory. From your own
project, you should include the headers for libraries by
backing out of the project folder, go into the code library
folder, src, and the header file's name.
	
	Example:
	#include "../Noritake_VFD_CUU/src/Noritake_VFD_CUU.h"
	In your own project's main.cpp.
	
File structure:
        Noritake_VFD
        |
        +------->Noritake_VFD_CUU
        |        |
        |        +------->src
        |        |        |
        |        |        +------->config.h
        |        |        +------->interface.h
        |        |        +------->Noritake_VFD_CUU.cpp
        |        |        +------->Noritake_VFD_CUU.h
        |        |        +------->paralleli80.cpp
        |        |        +------->parallelm68.cpp
        |        |        +------->serial.cpp
        |        |        +------->... (source files) ...
        |        |
        |        +------->doc
        |                 |
        |                 +------->configuration.txt
        |                 +------->initialization.txt
        |                 +------->methods.txt
        |                 +------->... (documentation files) ...
        |
        +------->README.txt 

----------------------------------------------------------------
GETTING STARTED

USING DEMO PROJECTS

	1) Download the code library and a demo project for the
	  CU-U VFD module: http://noritake-elec.com
	2) Extract the code library file to the Desktop. The
	  desktop should contain a folder named Noritake_VFD.
	  Inside that folder should be the name of your
	  module's code library.
		Example: Noritake_VFD\Noritake_VFD_CUU
		would be the path to the code library if
		for CU-U VFDs.
	3) Extract the contents of the demo file into the
	  Noritake_VFD\Noritake_VFD_CUU directory. Now that
      directory should contain the src and doc directories,
      README.txt, and demo project folder.
	4) Open the .aps project file in AVR Studio 4
       or the .atsln project file in Atmel Studio 6.
	5) Set the configuration options according to your
	  hardware in config.h. See doc\configuration.txt for
	  details.
	6) Build the demo and program the host system.


MAKING YOUR OWN PROJECT

	1) Create a project in AVR Studio 4 or Atmel Studio 6.
	2) Set the configuration options according to your
	   hardware in config.h. See doc\configuration.txt for
	   details.
	3) Add all of the .h and .cpp files in src to your
	   your project.
	4) Create a main.cpp.
	5) Create an instance of the class Noritake_VFD_CUU.
	6) Initialize the VFD module with the CUU_init() method.
	7) Use the print methods to print a message.
	8) Compile and program the host system.

	Example:
	
	#include "../src/Noritake_VFD_CUU.h"
	int main() {
		Noritake_VFD_CUU vfd;
		vfd.CUU_init();
		vfd.println("Noritake");
		vfd.print("VFD");
	}
	
----------------------------------------------------------------
E-M-0051-01 06/25/2012
----------------------------------------------------------------
CHANGES
Revision 1
    The directory structure has changed so that the demo
    projects go into the Noritake_VFD_CUU directory not the
    Noritake_VFD directory.
    Instructions for Atmel Studio 6 was added.

SUPPORT

For further support, please contact:
	Noritake Co., Inc.
	2635 Clearbrook Dr 
	Arlington Heights, IL 60005 
	800-779-5846 
	847-439-9020
	support.ele@noritake.com

All rights reserved. © Noritake Co., Inc.