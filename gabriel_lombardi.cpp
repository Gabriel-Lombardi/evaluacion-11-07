// GIMNASIO
#include <stdio.h>
#include <stdbool.h>

#define NUM_CLASES 4
#define NUM_HORARIOS 5

void menu() { // menu para el usuario
    printf("=== GIMNASIO ===\n");
    printf("\nEste programa sirve para hacer un informe sobre:\n");
    printf("\tEl total de asistentes de cada clase del gimnasio.\n");
    printf("\tLa clase a la cual no asistio nadie.\n");
    printf("\tEl horario al cual no asistio nadie.\n");
    printf("\tLa ganancia total del gimnasio.\n");
    printf("\nLas clases son: Top Ride\n");
    printf("\t\tZumba\n\t\tEntrenamiento\n\t\tAbdominales\n");
    printf("\nPara poder hacer el informe correctamente, indique lo que se le pide a continuacion...\n");
}

int main(void) {
    // definimos las variables a utilizar
    int  asistencia[NUM_CLASES][NUM_HORARIOS] = {0};
    int  cupo[NUM_CLASES] = {15,15,20,15};
    int  totalAsistentes  = 0;
    int  gananciaTotal    = 0;
    int  horario, clase;
    char clases[NUM_CLASES][20]     = {"Top Ride", "Zumba", "Entrenamiento", "Abdominales"};
    char horarios[NUM_HORARIOS][10] = {"Horario 1", "Horario 2", "Horario 3", "Horario 4", "Horario 5"};
    bool hayClaseSinAsistentes = false; // caso base
    bool hayHorarioVacio       = false; // caso base

    menu();
    // ingresar la cantidad de asistentes de cada clase
    for (horario = 0; horario < NUM_HORARIOS; horario++) {
        printf("\n---------------------\n");
        // printf("Horario %d:\n", horario + 1);
        printf("%s:\n", horarios[horario]);

        bool hayCupo = false; // caso base

        for (clase = 0; clase < NUM_CLASES; clase++) {
            int asistentes;

            asistentes:
            printf("Ingrese la cantidad de asistentes para la clase %s: ", clases[clase]);
            scanf(" %d", &asistentes);

            if (asistentes <= cupo[clase]) {
                asistencia[clase][horario] = asistentes;
                cupo[clase] -= asistentes;
                totalAsistentes += asistentes;
                gananciaTotal += asistentes * ((horario == 2) ? 700 : (horario < 2) ? 700 * 0.8 : 700 * 1.15);

                hayCupo = true;
            } else {
                printf("No hay cupo suficiente para la clase '%s' en este horario.\n", clases[clase]);
                goto asistentes; // si no hay cupos suficientes para esa cantidad de personas el programa vuelve a preguntar
            }
        }

        if (hayCupo == false) hayHorarioVacio = true;
    }

    // clase sin asistentes
    printf("\nClase sin asistentes:\n");
    for (clase = 0; clase < NUM_CLASES; clase++) {
        int asistentesClase = 0;
        for (horario = 0; horario < NUM_HORARIOS; horario++) {
            asistentesClase += asistencia[clase][horario];
        }

        if (asistentesClase == 0) {
            printf("%s\n", clases[clase]);
            hayClaseSinAsistentes = true;
        }
    }

    if (hayClaseSinAsistentes == false) printf("No hay clases sin asistentes\n");

    // horario sin clases
    printf("\nHorario sin clases:\n");
    for (horario = 0; horario < NUM_HORARIOS; horario++) {
        bool hayClase = false;
        for (clase = 0; clase < NUM_CLASES; clase++) {
            if (asistencia[clase][horario] > 0) {
                hayClase = true;
                break;
            }
        }

        if (hayClase == false) printf("Horario %d\n", horario + 1);
    }

    // cantidad de personas por clase
    printf("\nCantidad de personas que asistieron a cada clase:\n");
    for (clase = 0; clase < NUM_CLASES; clase++) {
        int totalClase = 0;
        for (horario = 0; horario < NUM_HORARIOS; horario++) {
            totalClase += asistencia[clase][horario];
        }
        printf("%s: %d\n", clases[clase], totalClase);
    }

    // ganancia total
    printf("\nLa ganancia total es de: $%d", gananciaTotal);
    
    return 0;
}