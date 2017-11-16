@REM Compilación y Enlace con librería gráfica.
@cls


cl /nologo /Zi /GR- /EHs /W4 /MD ..\src\memory_node.c -I ..\deps
@echo  Proceso por lotes finalizado.
@echo -------------------------------