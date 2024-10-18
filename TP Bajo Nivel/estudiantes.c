#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estudiantes.h"

#define NOMBRE_LENGTH 100

void agregarEstudiante(Estudiante **estudiantes, const char *nombre, int edad)
{
    Estudiante *nuevo_estudiante = (Estudiante *)malloc(sizeof(Estudiante));
    if (nuevo_estudiante == NULL)
    {
        printf(RED "Error de memoria\n" RESET);
        return;
    }
    strncpy(nuevo_estudiante->nombre, nombre, NOMBRE_LENGTH);
    nuevo_estudiante->nombre[NOMBRE_LENGTH - 1] = '\0';
    nuevo_estudiante->edad = edad;
    nuevo_estudiante->materias = NULL;
    nuevo_estudiante->cantidad_materias = 0;
    nuevo_estudiante->next = *estudiantes;
    *estudiantes = nuevo_estudiante;
}

Estudiante *buscar_estudiante(Estudiante *estudiante, const char *nombre)
{
    Estudiante *temp_estudiante = estudiante;
    while (temp_estudiante != NULL)
    {
        if (strcmp(temp_estudiante->nombre, nombre) == 0)
        {
            return temp_estudiante;
        }
        temp_estudiante = temp_estudiante->next;
    }
    return NULL;
}

void agregarMateria(Estudiante *estudiante, const char *nombre_estudiante, const char *nombre_materia)
{
    Estudiante *estudiante_buscado = buscar_estudiante(estudiante, nombre_estudiante);
    if (estudiante_buscado == NULL)
    {
        printf(RED "Estudiante No encontrado\n" RESET);
        return;
    }

    MateriaNode *nueva_materia = (MateriaNode *)malloc(sizeof(MateriaNode));
    if (nueva_materia == NULL)
    {
        printf(RED "Error de memoria\n" RESET);
        return;
    }

    strncpy(nueva_materia->materia.nombre, nombre_materia, NOMBRE_LENGTH);
    nueva_materia->materia.nombre[NOMBRE_LENGTH - 1] = '\0';
    nueva_materia->materia.aprobado_bool = -1;
    nueva_materia->materia.calificacion = 0;
    nueva_materia->next = estudiante_buscado->materias;
    estudiante_buscado->materias = nueva_materia;
    estudiante_buscado->cantidad_materias++;
    return;
}

void mostrar_todos_los_estudiantes(Estudiante *estudiante)
{
    Estudiante *temp_estudiante = estudiante;
    while (temp_estudiante != NULL)
    {
        printf(BLUE "Nombre: %s, Edad: %d\n" RESET, temp_estudiante->nombre, temp_estudiante->edad );
        temp_estudiante = temp_estudiante->next;
    }
    return;
}

void mostrar_todos_las_materias(Estudiante *estudiante)
{
    Estudiante *temp_estudiante = estudiante;
    while (temp_estudiante != NULL)
    {
        MateriaNode *temp_materia = temp_estudiante->materias;
        printf(BLUE "Nombre del estudiante: %s\n" RESET, temp_estudiante->nombre);
        while (temp_materia != NULL)
        {
            printf(MAGENTA "Materia: %s\n" RESET, temp_materia->materia.nombre);
            temp_materia = temp_materia->next;
        }
        temp_estudiante = temp_estudiante->next;
    }
    return;
}

void dar_de_baja_estudiante(Estudiante **estudiante, const char *nombre)
{
    Estudiante *temp_estudiante = *estudiante;
    Estudiante *previo = NULL;

    while (temp_estudiante != NULL)
    {
        if (strcmp(temp_estudiante->nombre, nombre) == 0)
        {
            if (previo == NULL)
            {
                *estudiante = temp_estudiante->next;
            }
            else
            {
                previo->next = temp_estudiante->next;
            }
            borrar_todas_las_materias(temp_estudiante, nombre);
            memset(temp_estudiante, 0, sizeof(Estudiante));
            free(temp_estudiante);
            printf(BLUE "Estudiante dado de baja.\n" RESET);
            return;
        }
        previo = temp_estudiante;
        temp_estudiante = temp_estudiante->next;
    }
    printf(RED "Estudiante No encontrado\n" RESET);
    return;
}

void dar_de_baja_materia(Estudiante *estudiante, const char *nombre_estudiante, const char *nombre_materia)
{
    Estudiante *estudiante_buscado = buscar_estudiante(estudiante, nombre_estudiante);

    if (estudiante_buscado == NULL)
    {
        printf(RED "Estudiante No encontrado\n" RESET);
        return;
    }
    MateriaNode *temp_materia = estudiante_buscado->materias;
    MateriaNode *materia_previa = NULL;

    while (temp_materia != NULL)
    {
        if (strcmp(temp_materia->materia.nombre, nombre_materia) == 0)
        {
            if (materia_previa == NULL)
            {
                estudiante_buscado->materias = temp_materia->next;
            }
            else
            {
                materia_previa->next = temp_materia->next;
            }
            estudiante_buscado->cantidad_materias--;
            memset(temp_materia, 0, sizeof(MateriaNode));
            free(temp_materia);
            printf(BLUE "Materia eliminada\n" RESET);
            return;
        }
        materia_previa = temp_materia;
        temp_materia = temp_materia->next;
    }
    printf(RED "Materia No encontrada\n" RESET);
    return;
}

void consultar_cantidad_de_materias(Estudiante *estudiante, const char *nombre_estudiante)
{
    Estudiante *estudiante_buscado = buscar_estudiante(estudiante, nombre_estudiante);

    if (estudiante_buscado == NULL)
    {
        printf(RED "Estudiante No encontrado\n" RESET);
        return;
    }

    printf("El alumno esta cursando %d materias\n", estudiante_buscado->cantidad_materias);
    return;
}

void cargar_calificacion_de_examen(Estudiante *estudiante, const char *nombre_alumno, const char *nombre_materia, int nota)
{
    Estudiante *estudiante_buscado = buscar_estudiante(estudiante, nombre_alumno);
    if (estudiante_buscado == NULL)
    {
        printf(RED "Estudiante No encontrado\n" RESET);
        return;
    }
    MateriaNode *temp_materia = estudiante_buscado->materias;

    while (temp_materia != NULL)
    {
        if (strcmp(temp_materia->materia.nombre, nombre_materia) == 0)
        {
            temp_materia->materia.calificacion = nota;
            if (nota >= 4)
            {
                temp_materia->materia.aprobado_bool = 1;
                printf("Nota cargada\n");
                return;
            }
            else
            {
                temp_materia->materia.aprobado_bool = 0;
                printf("Nota cargada\n");
                return;
            }
        }
        temp_materia = temp_materia->next;
    }
    printf(RED "Materia No encontrada\n" RESET);
    return;
}

void consultar_aprobacion(Estudiante *estudiante, const char *nombre_alumno, const char *nombre_materia)
{
    Estudiante *estudiante_buscado = buscar_estudiante(estudiante, nombre_alumno);
    if (estudiante_buscado == NULL)
    {
        printf(RED "Estudiante No encontrado\n" RESET);
        return;
    }
    MateriaNode *temp_materia = estudiante_buscado->materias;

    while (temp_materia != NULL)
    {
        if (strcmp(temp_materia->materia.nombre, nombre_materia) == 0)
        {
            if (temp_materia->materia.calificacion == 0)
            {
                printf("El alumno no rindio la materia todavia.\n");
                return;
            }
            if (temp_materia->materia.aprobado_bool == 1)
            {
                printf("El alumno aprobo la materia\n");
                return;
            }
            else
            {
                printf("El alumno desaprobo la materia\n");
                return;
            }
        }
        temp_materia = temp_materia->next;
    }
    printf(RED "Materia No encontrada\n" RESET);
    return;
}

void promedios_de_un_alumno(Estudiante *estudiante, const char *nombre_alumno)
{
    int promedios = 0;

    Estudiante *estudiante_buscado = buscar_estudiante(estudiante, nombre_alumno);
    if (estudiante_buscado == NULL)
    {
        printf(RED "Estudiante No encontrado\n" RESET);
        return;
    }

    if (estudiante_buscado->cantidad_materias == 0)
    {
        printf(RED "El alumno no rindio ninguna materia\n" RESET);
        return;
    }

    MateriaNode *temp_materia = estudiante_buscado->materias;

    while (temp_materia != NULL)
    {
        promedios = promedios + temp_materia->materia.calificacion;
        temp_materia = temp_materia->next;
    }

    promedios = promedios / estudiante_buscado->cantidad_materias;
    printf(BLUE "El alumno tiene un promedio de:%d\n" RESET, promedios);
    return;
}

void aprobados_por_materia(Estudiante *estudiante, const char *nombre_materia)
{
    int cantidad_aprobados = 0;
    Estudiante *estudiante_temp = estudiante;
    while (estudiante_temp != NULL)
    {
        MateriaNode *materia_temp = estudiante_temp->materias;
        while (materia_temp != NULL)
        {
            if (strcmp(materia_temp->materia.nombre, nombre_materia) == 0)
            {
                if (materia_temp->materia.aprobado_bool == 1)
                {
                    cantidad_aprobados++;
                }
                break;
            }
            materia_temp->next;
        }
        estudiante_temp = estudiante_temp->next;
    }
    printf(BLUE "La cantidad de aprobados en la materia %s es %d\n" RESET, nombre_materia, cantidad_aprobados);
    return;
}

void borrar_todas_las_materias(Estudiante *estudiante, const char *nombre)
{
    Estudiante *estudiante_buscado = buscar_estudiante(estudiante, nombre);
    if (estudiante_buscado == NULL)
    {
        printf(RED "Estudiante No encontrado\n" RESET);
        return;
    }

    MateriaNode *temp_materia = estudiante_buscado->materias;

    while (temp_materia != NULL)
    {
        MateriaNode *aux = temp_materia->next;
        memset(temp_materia, 0, sizeof(MateriaNode));
        free(temp_materia);
        temp_materia = aux;
    }
    return;
}

void borrar_todos_los_estudientes(Estudiante *estudiante)
{
    while (estudiante != NULL)
    {
        Estudiante *siguiente_estudiante = estudiante->next;
        borrar_todas_las_materias(estudiante, estudiante->nombre);
        memset(estudiante, 0, sizeof(Estudiante));
        free(estudiante);
        estudiante = siguiente_estudiante;
    }
    return;
}