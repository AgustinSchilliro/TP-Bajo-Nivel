#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estudiantes.h"
#include "estudiantes.c"

int menu()
{
    int lectura = 0;
    printf("======Menu de Estudiantes=====\n");
    printf("Opcion 1: Agregar un estudiante\n");
    printf("Opcion 2: Buscar un estudiante\n");
    printf("Opcion 3: Agregar materia a un estudiante\n");
    printf("Opcion 4: Mostrar todos los estudiantes\n");
    printf("Opcion 5: Mostrar todas las materias de todos los estudiantes\n");
    printf("Opcion 6: Dar de baja un estudiante de una materia\n");
    printf("Opcion 7: Dar de baja a un estudiante\n");
    printf("Opcion 8: Subir la nota de un estudiante\n");
    printf("Opcion 9: Consultar si un estudiante aprobo una materia\n");
    printf("Opcion 10: Consultar promedio de un alumno\n");
    printf("Opcion 11: Consultar la cantidad de aprobados de una materia\n");
    printf("Opcion 12: Reiniciar el programa.\n");
    printf("Opcion 13: Salir el programa.\n");
    printf("Ingrese una opcion\n");
    fflush(stdin);
    scanf("%d", &lectura);
    fflush(stdin);

    return lectura;
}

void pedir_materia(const char nombre_materia[NOMBRE_LENGTH])
{
    printf("Ingrese el nombre de la materia\n");
    gets(nombre_materia);
    fflush(stdin);
}

void pedir_nombre(const char nombre_estudiante[NOMBRE_LENGTH])
{
    printf("Ingrese el nombre del estudiante\n");
    gets(nombre_estudiante);
    fflush(stdin);
}

int main()
{
    int opcion;
    Estudiante *head_estudiante = NULL;
    do
    {
        opcion = menu();
        switch (opcion)
        {
        case 1:
        {
            int edad;
            const char nombre[NOMBRE_LENGTH];
            pedir_nombre(nombre);
            printf("Ingrese la edad del estudiante\n");
            scanf("%d", &edad);
            fflush(stdin);
            agregarEstudiante(&head_estudiante, nombre, edad);
            printf("Estudiante Agregado\n");
            break;
        }

        case 2:
        {
            const char nombre[NOMBRE_LENGTH];
            pedir_nombre(nombre);
            Estudiante *estudiante_buscado = buscar_estudiante(head_estudiante, nombre);
            MateriaNode *materia_temp = estudiante_buscado->materias;
            printf("El estudiante tiene de nombre %s, su edad es %i y esta cursando las materias:\n", estudiante_buscado->nombre, estudiante_buscado->edad);
            while (materia_temp != NULL)
            {
                printf("Nombre de materia: %s\n", materia_temp->materia.nombre);
                materia_temp = materia_temp->next;
            }
            break;
        }
        case 3:
        {
            const char nombre_estudiante[NOMBRE_LENGTH];
            const char nombre_materia[NOMBRE_LENGTH];
            pedir_nombre(nombre_estudiante);
            pedir_materia(nombre_materia);
            agregarMateria(head_estudiante, nombre_estudiante, nombre_materia);
            printf("Materia agregada al estudiante\n");
            break;
        }
        case 4:
        {
            printf("Lista de estudiante:\n");
            mostrar_todos_los_estudiantes(head_estudiante);
            break;
        }
        case 5:
        {
            mostrar_todos_las_materias(head_estudiante);
            break;
        }
        case 6:
        {
            const char nombre_estudiante[NOMBRE_LENGTH];
            const char nombre_materia[NOMBRE_LENGTH];
            pedir_nombre(nombre_estudiante);
            pedir_materia(nombre_materia);
            dar_de_baja_materia(head_estudiante, nombre_estudiante, nombre_materia);
            printf("Estudiante dado de baja de la materia de la materia\n");
            break;
        }
        case 7:
        {
            const char nombre_estudiante[NOMBRE_LENGTH];
            pedir_nombre(nombre_estudiante);
            dar_de_baja_estudiante(head_estudiante, nombre_estudiante);
            printf("Estudiante dado de baja\n");
            break;
        }
        case 8:
        {
            int nota;
            const char nombre_estudiante[NOMBRE_LENGTH];
            const char nombre_materia[NOMBRE_LENGTH];
            pedir_nombre(nombre_estudiante);
            pedir_materia(nombre_materia);
            printf("Ingrese la edad del estudiante\n");
            scanf("%d", &nota);
            fflush(stdin);
            cargar_calificacion_de_examen(head_estudiante, nombre_estudiante, nombre_materia, nota);
            printf("Nota cargada\n");
            break;
        }
        case 9:
        {
            const char nombre_estudiante[NOMBRE_LENGTH];
            const char nombre_materia[NOMBRE_LENGTH];
            pedir_nombre(nombre_estudiante);
            pedir_materia(nombre_materia);
            consultar_aprobacion(head_estudiante, nombre_estudiante, nombre_materia);
            break;
        }
        case 10:
        {
            const char nombre[NOMBRE_LENGTH];
            pedir_nombre(nombre);
            promedios_de_un_alumno(head_estudiante, nombre);
            break;
        }
        case 11:
        {
            const char nombre_materia[NOMBRE_LENGTH];
            pedir_materia(nombre_materia);
            aprobados_por_materia(head_estudiante, nombre_materia);
            break;
        }
        case 12:
        {
            borrar_todos_los_estudientes(head_estudiante);
            break;
        }
        case 13:
        {
            printf("Saliendo del sistema...\n");
            borrar_todos_los_estudientes(head_estudiante);
        }
        default:
            printf("Opcion invalida.\n");
        }
    } while (opcion != 13);

    return 0;
}