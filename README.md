# Load Balancer Project

Este proyecto implementa un balanceador de carga simple utilizando servidores y una matriz de adyacencia para definir costos de conexión entre los servidores. Los servidores tienen un límite máximo de solicitudes, y la lógica de balanceo distribuye las peticiones basándose en este límite y el costo de conexión más bajo disponible.

## Caso 1 - Configuración básica de 4 Servidores

### Descripción de la Configuración

- **Número de servidores:** 4
- **Matriz de adyacencia (costos de conexión):**

[0, 1, 2, INF] 
[1, 0, INF, 3] 
[2, INF, 0, 4] 
[INF, 3, 4, 0]

En la matriz, `INF` representa la falta de conexión directa entre los servidores.

- **Carga máxima permitida por servidor:** 2 solicitudes

### Pruebas y Resultados

1. **Estado inicial de los servidores:**
 - Todos los servidores tienen una carga de 0 solicitudes.
 - Salida esperada:
   ```
   Cargas actuales de los servidores:
   Servidor 0: 0 solicitudes
   Servidor 1: 0 solicitudes
   Servidor 2: 0 solicitudes
   Servidor 3: 0 solicitudes
   ```

2. **Distribución de la primera solicitud desde el servidor 0:**
 - El balanceador busca el servidor con el menor costo de conexión desde el servidor 0.
 - La matriz muestra que el costo más bajo es `1` hacia el servidor 1.
 - Se asigna la solicitud al servidor 1.
 - Salida esperada:
   ```
   Solicitud asignada al Servidor 1 desde Servidor 0, Carga actual: 1
   ```

3. **Distribución de la segunda solicitud desde el servidor 0:**
 - El balanceador nuevamente busca el servidor con el menor costo desde el servidor 0.
 - El servidor 1 tiene una carga de 1 (no ha alcanzado el límite máximo), por lo que se le asigna otra solicitud.
 - Salida esperada:
   ```
   Solicitud asignada al Servidor 1 desde Servidor 0, Carga actual: 2
   ```

4. **Intento de distribución de una tercera solicitud desde el servidor 0:**
 - El servidor 1 ya alcanzó su límite de 2 solicitudes.
 - El balanceador busca el siguiente servidor con la conexión más baja disponible.
 - El servidor 2 tiene un costo de `2` y una carga de `0`, por lo que se selecciona.
 - Salida esperada:
   ```
   Solicitud asignada al Servidor 2 desde Servidor 0, Carga actual: 1
   ```

5. **Estado actual de los servidores:**
 - El balanceador muestra la carga actual de los servidores.
 - Salida esperada:
   ```
   Cargas actuales de los servidores:
   Servidor 0: 0 solicitudes
   Servidor 1: 2 solicitudes
   Servidor 2: 1 solicitudes
   Servidor 3: 0 solicitudes
   ```

6. **Completar una solicitud en el servidor 1:**
 - Se completa una solicitud, reduciendo la carga del servidor 1 de `2` a `1`.
 - Salida esperada:
   ```
   Solicitud completada en el Servidor 1, Carga actual: 1
   ```

7. **Nueva solicitud desde el servidor 0:**
 - El servidor 1 tiene una carga de `1`, por lo que el balanceador puede asignar una nueva solicitud.
 - Salida esperada:
   ```
   Solicitud asignada al Servidor 1 desde Servidor 0, Carga actual: 2
   ```

### Resumen de Resultados

El balanceador de carga distribuyó correctamente las solicitudes basándose en el límite máximo y los costos de conexión definidos en la matriz de adyacencia. Se manejó correctamente la situación en la que un servidor alcanzó su carga máxima y se buscó la siguiente mejor opción. Además, se verificó la correcta liberación de carga cuando una solicitud fue completada.

## Video - Salida Consola
https://drive.google.com/file/d/1R8mnNrG4dc9r79rfBB_zmzEeCg9IJgXz/view?usp=sharing