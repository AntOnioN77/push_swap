#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>
#include <string.h>

#define LONGITUD 6

typedef struct {
    int lista_anterior[LONGITUD];
    bool pares_usados[LONGITUD][LONGITUD];
    bool primera_llamada;
} Estado;

void inicializar_estado(Estado *estado) {
    memset(estado->lista_anterior, 0, sizeof(estado->lista_anterior));
    memset(estado->pares_usados, 0, sizeof(estado->pares_usados));
    estado->primera_llamada = true;
}

void numeros_mas_cercanos(int lista[], char *letra1, char *letra2, Estado *estado) {
    if (estado->primera_llamada || memcmp(lista, estado->lista_anterior, LONGITUD * sizeof(int)) != 0) {
        // Reiniciar el estado si es la primera llamada o la lista ha cambiado
        memcpy(estado->lista_anterior, lista, LONGITUD * sizeof(int));
        memset(estado->pares_usados, 0, sizeof(estado->pares_usados));
        estado->primera_llamada = false;
    }

    double diferencia_minima = DBL_MAX;
    int idx1 = -1, idx2 = -1;

    for (int i = 0; i < LONGITUD; i++) {
        for (int j = i + 1; j < LONGITUD; j++) {
            if (!estado->pares_usados[i][j]) {
                double diferencia = abs(lista[i] - lista[j]);
                if (diferencia < diferencia_minima) {
                    diferencia_minima = diferencia;
                    idx1 = i;
                    idx2 = j;
                }
            }
        }
    }

    if (idx1 != -1 && idx2 != -1) {
        *letra1 = 'A' + idx1;
        *letra2 = 'A' + idx2;
        estado->pares_usados[idx1][idx2] = true;
        estado->pares_usados[idx2][idx1] = true;
    } else {
        *letra1 = *letra2 = 'X';  // Indicador de que no se encontraron más pares
    }
}

bool busqueda_con_arbol_decision(int lista[], char *letra1, char *letra2, Estado *estado) {
    numeros_mas_cercanos(lista, letra1, letra2, estado);
    
    while (true) {
        if (*letra1 == 'X' && *letra2 == 'X') {
            return false;  // No quedan más pares
        }
        
        if ((*letra1 == 'A' && *letra2 == 'B') ||
            (*letra1 == 'B' && *letra2 == 'C') ||
            (*letra1 == 'E' && *letra2 == 'D') ||
            (*letra1 == 'E' && *letra2 == 'F') ||
            (*letra2 == 'A' && *letra1 == 'B') ||
            (*letra2 == 'B' && *letra1 == 'C') ||
            (*letra2 == 'E' && *letra1 == 'D') ||
            (*letra2 == 'E' && *letra1 == 'F')) {
            
            numeros_mas_cercanos(lista, letra1, letra2, estado);
        } else {
            return true;  // Búsqueda exitosa
        }
    }
}

void ejecutar_operaciones(char letra1, char letra2, int numeros[]) {
    int valor1 = numeros[letra1 - 'A'];
    int valor2 = numeros[letra2 - 'A'];

    if ((letra1 == 'B' && letra2 == 'F') || (letra2 == 'B' && letra1 == 'F')) {
        pb();
    }
    else if ((letra1 == 'B' && letra2 == 'E') || (letra2 == 'B' && letra1 == 'E')) {
        pb();
    }
    else if ((letra1 == 'A' && letra2 == 'E') || (letra2 == 'A' && letra1 == 'E')) {
        ra();
        pb();
    }
    else if ((letra1 == 'C' && letra2 == 'E') || (letra2 == 'C' && letra1 == 'E')) {
        rra();
        pb();
    }
    else if ((letra1 == 'B' && letra2 == 'D') || (letra2 == 'B' && letra1 == 'D')) {
        pb();
        sb();
    }
    else if ((letra1 == 'A' && letra2 == 'F') || (letra2 == 'A' && letra1 == 'F')) {
        ra();
        pb();
    }
    else if ((letra1 == 'C' && letra2 == 'F') || (letra2 == 'C' && letra1 == 'F')) {
        ra();
        pb();
    }
    else if ((letra1 == 'A' && letra2 == 'D') || (letra2 == 'A' && letra1 == 'D')) {
        ra();
        rb();
        pb();
    }
    else if ((letra1 == 'C' && letra2 == 'D') || (letra2 == 'C' && letra1 == 'D')) {
        rra();
        rb();
        pb();
    }
    else if ((letra1 == 'A' && letra2 == 'C') || (letra2 == 'A' && letra1 == 'C')) {
        if ((letra1 == 'A' && valor1 > valor2) || (letra2 == 'A' && valor2 > valor1)) {
            rra();
            sa();
        } else {
            ra();
        }
    }
    else if ((letra1 == 'D' && letra2 == 'F') || (letra2 == 'D' && letra1 == 'F')) {
        if ((letra1 == 'D' && valor1 < valor2) || (letra2 == 'D' && valor2 < valor1)) {
            rrb();
            sb();
        } else {
            rb();
        }
    }
    else {
        printf("Combinación de letras no reconocida: %c y %c\n", letra1, letra2);
    }
}


int main() {
    int numeros[] = {10, 5, 8, 12, 3, 7};
    char letra1, letra2;
    Estado estado;
    inicializar_estado(&estado);

    bool exito = busqueda_con_arbol_decision(numeros, &letra1, &letra2, &estado);

    if (exito) {
        printf("Búsqueda exitosa. Los números más cercanos son: %c y %c\n", letra1, letra2);
        printf("Que corresponden a los valores: %d y %d\n", 
               numeros[letra1 - 'A'], numeros[letra2 - 'A']);
        
        printf("Ejecutando operaciones para %c y %c:\n", letra1, letra2);
        ejecutar_operaciones(letra1, letra2, numeros);
    } else {
        printf("No se encontró un par que cumpla con los criterios del árbol de decisión.\n");
    }

    return 0;
}
