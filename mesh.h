#ifndef MESH_H
#define MESH_H
#include "C:\\Users\\salve\\source\\repos\\3DRenderer\\vectors.h"
#include "triangle.h"


#define N_CUBE_VERTICES 8
#define N_CUBE_FACES (6 * 2) //cubo ha sei facce, 2 triangoli per ogni faccia


extern face_t cube_faces[N_CUBE_FACES];
extern vec3_t cube_vertices[N_CUBE_VERTICES];
void    load_cube_mesh_data(void);
void    load_obj_file_data(char* filename);


/////////////////////////////////////
//Definisce una struct per dimensioni di mesh dinamiche, con array face e aray vertici
//////////////////////////////////////

typedef struct mesh_t {
	vec3_t* vertices;	//array dinamico di vertici
	face_t* faces;		//array dinamico di faccia 
	vec3_t rotation;	//rotazione con i valori x y e z ANGOLI DI EULERO EULER ANGLES 
	vec3_t scale;		//ci serve per scalare la matrice di tot 
	vec3_t translate;	// traslazione della matrice. 
}mesh_t;

extern mesh_t mesh; //mesh globale 


#endif