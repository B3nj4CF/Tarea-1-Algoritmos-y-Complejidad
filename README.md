# TAREA 1 INF221 2026-1

## Estructura del Repositorio

Este repositorio contiene la documentación, el código fuente y las instrucciones necesarias para la realización de la Tarea 1 de la asignatura *INF221 Algoritmos y Complejidad*.

**Entrega:** archivo `.zip` vía aula.usm.cl

A continuación, se describe la estructura del repositorio:

```bash
├── assignment_statement
├── code
├── report
└── README.md
```

### `assignment_statement`
Contiene el enunciado de la tarea, así como los archivos fuente del enunciado en formato LaTeX (.tex).

### `code`
Contiene la plantilla de los archivos que deberán estar presentes en la entrega de la tarea. En ella, se deben implementar los algoritmos solicitados, los cuales se detallan a continuación:
- `matrix_multiplication`: Algoritmo de Strassen y versión Naive.
- `sorting`: std::sort, merge sort, quick sort.

### `report`
En esta carpeta se encuentra la plantilla en LaTeX para la elaboración del mini-informe correspondiente a la tarea.

***Para obtener información más detallada sobre el contenido de cada carpeta, se recomienda revisar los archivos README ubicados dentro de ellas.***


## Notas Personales

1. Los makeFiles tan disenados para que solo haya que ejecutar comados justos, make inputs, make clean, make run_all, make graficos (lo ideal seria en ese orden para ambos casos)
2. Algunos codigos son conbinacion de varios encontrados en internet y en la bibliografia ya que para arreglo de 10**7 se hacian pesados entonces para que fucniones se modificaron cosas eso extrapolado a la multiplicacion de matrices
3. No quedop bien claro como se tenia que hacer el mini informe, asi que paso la carpeta report a Overleaf en internet y desde ahi se trabajo el Latex, Se intento ser lo mas claro y manterlo dentro de los margenes
4. Los input se envian vaciios para poder comprimirlo y que se pueda enviar por aula
5. Se modico los generadores de los input ya que habia errores en la ruta de donde se guardaban
6. Es necesario tener las librerias usadas para que no haya fallos
7. Se uso Archlinux como el sistema asi que ojo con eso porfa por que puede que en windows WSL no funcione, no lo se
8. Se intento que el codigo quedara ordenado y limpio a la vista