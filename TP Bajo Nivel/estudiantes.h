#ifndef ESTUDIANTES_H
#define ESTUDIANTES_H

#define NOMBRE_LENGTH 100
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[36m"



// Struct Materia
typedef struct
{
    char nombre[NOMBRE_LENGTH];
    int calificacion;  // 0 - Si no tuvo examen todavia
    int aprobado_bool; // 0 False / 1 True
} Materia;

typedef struct MateriaNode
{
    Materia materia;
    struct MateriaNode *next;
}MateriaNode;


// Struct Estudiante
typedef struct Estudiante 
{
    char nombre[NOMBRE_LENGTH];
    int edad;
    int cantidad_materias;
    MateriaNode *materias; // Lista de materias para cada estudiantes
    struct Estudiante *next;
} Estudiante;

void agregarEstudiante(Estudiante** estudiantes, const char *nombre, int edad);
Estudiante *buscar_estudiante(Estudiante *estudiante, const char *nombre);
void agregarMateria(Estudiante *estudiante, const char *nombre_estudiante, const char *nombre_materia);
void mostrar_todos_los_estudiantes(Estudiante *estudiante);
void mostrar_todos_las_materias(Estudiante *estudiante);
void dar_de_baja_estudiante(Estudiante **estudiante, const char *nombre);
void dar_de_baja_materia(Estudiante *estudiante, const char *nombre_estudiante, const char *nombre_materia);
void cargar_calificacion_de_examen(Estudiante *estudiante, const char *nombre_alumno, const char *nombre_materia, int nota);
void consultar_cantidad_de_materias(Estudiante *estudiante, const char *nombre_estudiante);
void consultar_aprobacion(Estudiante *estudiante, const char *nombre_alumno, const char *nombre_materia);
void promedios_de_un_alumno(Estudiante *estudiante, const char *nombre_alumno);
void aprobados_por_materia(Estudiante *estudiante, const char *nombre_materia);
void borrar_todos_los_estudientes(Estudiante **estudiante);
void borrar_todas_las_materias(Estudiante *estudiante, const char *nombre);

#endif 