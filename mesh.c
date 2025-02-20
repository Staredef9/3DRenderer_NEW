#include "mesh.h"
#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


mesh_t mesh = {
    .vertices = NULL,
    .faces = NULL,
    .rotation = {0,0,0},
    .scale = {1.0,1.0,1.0},
    .translate = {0,0,0}
};

vec3_t cube_vertices[N_CUBE_VERTICES] = {
    {.x = -1, .y = -1, .z = -1},
    {.x = -1, .y = 1, .z = -1},
    {.x = 1, .y = 1, .z = -1},
    {.x = 1, .y = -1, .z = -1},
    {.x = 1, .y = 1, .z = 1},
    {.x = 1, .y = -1, .z = 1},
    {.x = -1, .y = 1, .z = 1},
    {.x = -1, .y = -1, .z = 1},
};


face_t cube_faces[N_CUBE_FACES] = {

    //lato frontale
    {.a = 1, .b = 2 , .c = 3, .color = 0xFFFF0000},
    {.a = 1, .b = 3 , .c = 4, .color = 0xFFFF0000},

    //lato destro 
    {.a = 4, .b = 3 , .c = 5, .color = 0xFF00FF00},
    {.a = 4, .b = 5 , .c = 6, .color = 0xFF00FF00},

    //lato retro 
    {.a = 6, .b = 5 , .c = 7, .color = 0xFF0000FF},
    {.a = 6, .b = 7 , .c = 8, .color = 0xFF0000FF},

    //lato sinistro
    {.a = 8, .b = 7 , .c = 2, .color = 0xFFFFFF00},
    {.a = 8, .b = 2 , .c = 1, .color = 0xFFFFFF00},

    //lato superiore
    {.a = 2, .b = 7 , .c = 5, .color = 0xFFFF00FF},
    {.a = 2, .b = 5 , .c = 3, .color = 0xFFFF00FF},

    //lato inferiore
    {.a = 6, .b = 8 , .c = 1, .color = 0xFF00FFFF},
    {.a = 6, .b = 1, .c = 4,  .color = 0xFF00FFFF}
};


void    load_cube_mesh_data(void) {

    for (int i = 0; i < N_CUBE_VERTICES; i++) {
        vec3_t cube_vertex = cube_vertices[i];
        array_push(mesh.vertices, cube_vertex);
    }
    for (int i = 0; i < N_CUBE_FACES; i++) {
        face_t cube_face = cube_faces[i];
        array_push(mesh.faces, cube_face);
    }
}



int    file_scanner_length(FILE* file) {
    char ch; 
    int length = 0;

    while ((ch = fgetc(file)) != EOF) {
        length++;
    }
    fseek(file, 0, SEEK_SET);

    return length;

}

void    file_scanner_filler(FILE* file,   int length)
{
    char *line = malloc(sizeof(char) * length);

    while(fgets(line, length, file)) {
        if (strncmp(line, "v ", 2) == 0)
        {
            vec3_t vertex;
            sscanf_s(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
            array_push(mesh.vertices, vertex);
        }

        if (strncmp(line, "f ", 2) == 0) {

            int vertex_indices[3];
            int texture_indices[3];
            int normal_indices[3];

            sscanf_s(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                &vertex_indices[0], &texture_indices[0], &normal_indices[0],
                &vertex_indices[1], &texture_indices[1], &normal_indices[1], 
                &vertex_indices[2], &texture_indices[2], &normal_indices[2]
            );
            face_t face = {
                .a = vertex_indices[0],
                .b = vertex_indices[1],
                .c = vertex_indices[2]
            };
            array_push(mesh.faces, face);
        }
    }

    printf("completed loading vertex and faces\n");
    free(line);
}

void    load_obj_file_data(char* filename) {

    //leggi il file, aprilo leggi il contenuti
    //parsalo per vertici e facce
    //carica quelle dentro la mesh faces e mesh vertex
    //LOOPPA e/ un vertice che comincia con v?
    //allora carica nei vertiic
    //Loppa e' un robo ceh comincia con F
    //allora carica su faces 
    FILE* file; 
    fopen_s(&file, filename, "r");

    if (file == NULL) {
        perror("Unable to open file!");
        exit(1);
    }

    int length = file_scanner_length(file);
   // printf("%d\n", length);

   file_scanner_filler(file, length);

    printf("file loaded!\n");



}