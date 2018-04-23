@REM Compilación y Enlace con librería gráfica.
@cls


cl /nologo /GR- /EHs /W4 /c /MD ..\src\memory_node.c -I ..\include
cl /nologo /GR- /EHs /W4 /c /MD ..\src\adt_list.c -I ..\include
cl /nologo /GR- /EHs /W4 /c /MD ..\src\main.c -I ..\include
cl /nologo /GR- /EHs /MD /Fe:..\bin\main.exe main.obj memory_node.obj adt_list.obj 
@echo  Proceso por lotes finalizado.
@echo -------------------------------