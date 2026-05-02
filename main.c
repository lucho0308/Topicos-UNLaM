#include <stdio.h>
#include <ctype.h> // Para isalpha



// Calcula el largo de la cadena
size_t mStrlen(const char* cadena) {
    size_t cont = 0;
    while (*cadena) {
        cont++;
        cadena++;
    }
    return cont;
}

// Busca un caracter y retorna su direccion
char* mStrchr(char* cadena, int car) {
    char* encontrado = NULL;
    while (*cadena && !encontrado) {
        if (*cadena == car)
            encontrado = cadena;
        else
            cadena++;
    }
    return encontrado;
}

/* --- Lógica de desofuscación --- */

void desofuscar(char* frase, const char* grupo) {
    char* p = frase;
    int tamGrupo = (int)mStrlen(grupo); // Usamos mStrlen

    while (*p != '\0') {
        // Usamos isalpha para detectar el inicio de cada palabra
        if (isalpha(*p)) {
            int posPalabra = 1;

            // Procesamos la palabra letra por letra
            while (*p != '\0' && isalpha(*p)) {

                // Buscamos si la letra actual está en el grupo
                char* hallado = mStrchr((char*)grupo, *p);

                if (hallado != NULL) {
                    // Calculamos el índice con aritmética de punteros
                    int indiceActual = hallado - grupo;
                    int nuevoIndice = indiceActual + posPalabra;

                    // Si nos pasamos del final del grupo, restamos para volver al inicio
                    if (nuevoIndice >= tamGrupo) {
                        nuevoIndice = nuevoIndice - tamGrupo;
                    }

                    // Reemplazamos usando el "atajo" de los corchetes
                    *p = grupo[nuevoIndice];
                }

                p++;
                posPalabra++;
            }
        } else {
            // Si es un espacio o puntuación, solo avanzamos
            p++;
        }
    }
}

int main() {
    // La frase de Isaac Asimov (Ejercicio 1.10)
    char texto[] = "Nj qemh v ljs kraenkqbres; lj oqe qemh es oqevorme sgn ellhs --Istqt Asdmgj";
    const char* miGrupo = "abcdghijkoqtuv";

    printf("Original:  %s\n", texto);

    desofuscar(texto, miGrupo);

    printf("Resultado: %s\n", texto);

    return 0;
}
