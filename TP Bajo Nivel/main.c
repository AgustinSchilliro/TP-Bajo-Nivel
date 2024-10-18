#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estudiantes.h"
#include "estudiantes.c"


int menu()
{
    int lectura = 0;
    printf(BLUE  "======Menu de Estudiantes=====\n"  RESET);
    printf(YELLOW "Opcion 1: Agregar un estudiante\n" RESET);
    printf(YELLOW "Opcion 2: Buscar un estudiante\n" RESET);
    printf(YELLOW "Opcion 3: Agregar materia a un estudiante\n" RESET);
    printf(YELLOW "Opcion 4: Mostrar todos los estudiantes\n" RESET);
    printf(YELLOW "Opcion 5: Mostrar todas las materias de todos los estudiantes\n" RESET);
    printf(YELLOW "Opcion 6: Dar de baja un estudiante de una materia\n" RESET);
    printf(YELLOW "Opcion 7: Dar de baja a un estudiante\n" RESET);
    printf(YELLOW "⬆Opcion 8: Subir la nota de un estudiante\n" RESET);
    printf(YELLOW "Opcion 9: Consultar si un estudiante aprobo una materia\n" RESET);
    printf(YELLOW "Opcion 10: Consultar promedio de un alumno\n" RESET);
    printf(YELLOW "Opcion 11: Consultar la cantidad de materias de un alumno\n" RESET);
    printf(YELLOW "Opcion 12: Consultar la cantidad de aprobados de una materia\n" RESET);
    printf(YELLOW "Opcion 13: Reiniciar el programa.\n" RESET);
    printf(RED "Opcion 14: Salir el programa.\n" RESET);
    printf(GREEN "Ingrese una opcion\n" RESET);
    fflush(stdin);
    scanf("%d", &lectura);
    fflush(stdin);

    return lectura;
}

void pedir_materia(const char nombre_materia[NOMBRE_LENGTH])
{
    printf(GREEN "Ingrese el nombre de la materia\n" RESET);
    gets(nombre_materia);
    fflush(stdin);
}

void pedir_nombre(const char nombre_estudiante[NOMBRE_LENGTH])
{
    printf(GREEN  "Ingrese el nombre del estudiante\n" RESET);
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
            printf(GREEN  "Ingrese la edad del estudiante\n" RESET);
            scanf("%d", &edad);
            fflush(stdin);
            agregarEstudiante(&head_estudiante, nombre, edad);
            printf(BLUE " Estudiante Agregado\n "RESET);
            break;
        }

        case 2:
        {
            const char nombre[NOMBRE_LENGTH];
            pedir_nombre(nombre);
            Estudiante *estudiante_buscado = buscar_estudiante(head_estudiante, nombre);
            if (estudiante_buscado == NULL)
            {
                printf(RED"El alumno no esta en la lista\n"RESET);
            }
            else
            {
            MateriaNode *materia_temp = estudiante_buscado->materias;
            printf(BLUE "El estudiante tiene de nombre %s, su edad es %i y esta cursando las materias:\n" RESET, estudiante_buscado->nombre, estudiante_buscado->edad);
            while (materia_temp != NULL)
            {
                printf(MAGENTA "Nombre de materia: %s\n" RESET, materia_temp->materia.nombre);
                materia_temp = materia_temp->next;
            }
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
            printf(BLUE "Materia agregada al estudiante\n" RESET);
            break;
        }
        case 4:
        {
            printf(MAGENTA"Lista de estudiante:\n" RESET);
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
            printf(RED "Estudiante dado de baja de la materia de la materia\n" RESET);
            break;
        }
        case 7:
        {
            const char nombre_estudiante[NOMBRE_LENGTH];
            pedir_nombre(nombre_estudiante);
            dar_de_baja_estudiante(&head_estudiante, nombre_estudiante);
            break;
        }
        case 8:
        {
            int nota;
            const char nombre_estudiante[NOMBRE_LENGTH];
            const char nombre_materia[NOMBRE_LENGTH];
            pedir_nombre(nombre_estudiante);
            pedir_materia(nombre_materia);
            printf(GREEN  "Ingrese la nota del estudiante\n" RESET);
            scanf("%d", &nota);
            fflush(stdin);
            cargar_calificacion_de_examen(head_estudiante, nombre_estudiante, nombre_materia, nota);
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
            const char nombre[NOMBRE_LENGTH];
            pedir_nombre(nombre);
            consultar_cantidad_de_materias(head_estudiante, nombre);
            break;
        }
        case 12:
        {
            const char nombre_materia[NOMBRE_LENGTH];
            pedir_materia(nombre_materia);
            aprobados_por_materia(head_estudiante, nombre_materia);
            break;
        }
        case 13:
        {
            borrar_todos_los_estudientes(&head_estudiante);
            printf(RED "Programa Reinciado\n" RESET);
            break;
        }
        case 14:
        {
            printf(RED "Saliendo del sistema...\n" RESET);
            borrar_todos_los_estudientes(&head_estudiante);
            break;
        }
        default:
            printf("Opcion invalida.\n");
        }
    } while (opcion != 14);

    return 0;
}