# Custom Game Shell
 University module work on extending a custom Engine

To build this program after running, open the solution with Visual Studio 2019.
Make sure DirectX 9 is installed and add the following dependencies :

1. Go to Project .... Properties... VC++ Directories ... Include Directories and add a new
folder. This will be the location of the DirectX SDK header files and is probably
“C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include;”.

2. Go to Project .... Properties... VC++ Directories ... Library Directories and add a new
folder. This will be the location of the DirectX SDK library files and is probably
“C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\lib\x86;”. 

3. Go to Project ... Properties ... Linker ... System. Set "SubSystem" to "Windows".

4. Go to Project ... Properties ... Advanced. Set "Character Set" to "Use Unicode".