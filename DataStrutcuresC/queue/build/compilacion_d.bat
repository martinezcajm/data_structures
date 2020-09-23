@REM Compilación y Enlace con librería gráfica.
@cls


cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\memory_node.c -I ..\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\adt_list.c -I ..\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\adt_queue.c -I ..\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\main.c -I ..\include
cl /nologo /Zi /GR- /EHs /MD /Fe:..\bin\main.exe main.obj memory_node.obj adt_list.obj adt_queue.obj
@echo  Proceso por lotes finalizado.
@echo -------------------------------