@echo off


set comp_flags=/Od /MD /Zi /EHsc /DGLFW_INCLUDE_NONE /DNDEBUG
set link_flags=/DEBUG /PDB:main.pdb
set files=..\src\main.cpp

set glad_include=/I..\vendor\glad\include
set glad_src=..\vendor\glad\src\glad.c

set win_libs=shell32.lib opengl32.lib user32.lib gdi32.lib
set vendor_dir=/LIBPATH:"..\vendor\glfw\lib-vc2022"
set vendor_libs=glfw3.lib

set includes=/I..\src /I..\vendor\glfw\include /I..\vendor\glad\include

if not exist .\build mkdir .\build
pushd .\build

ctime -begin stupid_time.ctm
if not exist glad.obj (
    echo "[LIBRARY_COMPILLING] Compilling Glad..."
    cl /MD %glad_include% /c %glad_src%
)

cl %comp_flags% %includes% /c %files% 
link /OUT:main.exe *.obj %link_flags% %vendor_dir%  %win_libs% %vendor_libs%

ctime -end stupid_time.ctm
popd 

