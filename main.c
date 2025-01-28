#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>
#include "display.h"
#include "C:\\Users\\salve\\source\\repos\\3DRenderer\\array.h"
#include "C:\\Users\\salve\\source\\repos\\3DRenderer\\vectors.h"
#include "C:\Users\salve\source\repos\3DRenderer\camera.h"
#include "C:\Users\salve\source\repos\3DRenderer\mesh.h"
//#define N_POINTS (9 * 9 * 9)
//vec3_t cube_points[N_POINTS]; // 9x9x9 cube
//vec2_t projected_points[N_POINTS];




//triangle_t triangles_to_render[N_MESH_FACES];
triangle_t* triangles_to_render = NULL;


vec3_t camera_position = { 0, 0, 0};
//vec3_t cube_rotation = { .x = 0, .y = 0, .z = 0 };

int			previous_frame_time = 0;

float fov_factor = 640;

bool is_running = false;

void setup(void) {
    // Allocate the required memory in bytes to hold the color buffer
    color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);

    // Creating a SDL texture that is used to display the color buffer
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );

    int point_count = 0;

    // Start loading my array of vectors
    // From -1 to 1 (in this 9x9x9 cube)
    /*for (float x = -1; x <= 1; x += 0.25) {
        for (float y = -1; y <= 1; y += 0.25) {
            for (float z = -1; z <= 1; z += 0.25) {
                vec3_t new_point = { .x = x, .y = y, .z = z };
                cube_points[point_count++] = new_point;
            }
        }
    }*/

    //load_cube_mesh_data();
    load_obj_file_data("Resources\\cube.obj");
    
   
}

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        is_running = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            is_running = false;
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Function that receives a 3D vector and returns a projected 2D point
// cambiando qua togliendo la divisione per z si ottinee una proiezione ISOMETRICA
// diminuendo a 128 anche il FOV sopra 
////////////////////////////////////////////////////////////////////////////////
vec2_t project(vec3_t point) {
    vec2_t projected_point = {
        .x = (fov_factor * point.x) / point.z,
        .y = (fov_factor * point.y) / point.z
    };
    return projected_point;
}

void update(void) {

    ////////////////////////////////////////////////////////////////////////////////
    ///tutto ok ma il while impiega un botto di memoria CPU 
    //meglio usare una DELAY FUNCTION che usa il sistema operativa 
    //tipo SDL DELAY, che usa le istruzioni del sistema operativo 
    //passa il controllo agli altri processii mentre aspetti
    //invece il while loop richiede l'attenzione della CPU per tutto il tempo di WAIT
    //NON BUONO
    //la libreria grafica di solito ha queste funzioni 
    /////////////////////////////////////////////////////////////////////////////////

   // while (!SDL_TICKS_PASSED(SDL_GetTicks(), previous_frame_time + FRAME_TARGET_TIME));
    //questo sopra e' un ciclo che aspetta wait time per il frame target time tra i frame 

    
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);
    //questa e' operazione corretta per risparmiare CPU 
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }
    
    previous_frame_time = SDL_GetTicks();

    triangles_to_render = NULL;

    mesh.rotation.y += 0.01;
    mesh.rotation.z += 0.00;
    mesh.rotation.x += 0.00;

    //looppa tutte le facce del quadrato e prende i vari punti 
    //di ogni faccia 
    int num_faces = array_length(mesh.faces);

    for (int i = 0; i < num_faces; i++) {
            
        face_t mesh_face = mesh.faces[i];

        vec3_t face_vertices[3];
        face_vertices[0] = mesh.vertices[mesh_face.a - 1];
        face_vertices[1] = mesh.vertices[mesh_face.b - 1];
        face_vertices[2] = mesh.vertices[mesh_face.c - 1];


        triangle_t projected_triangle;
        
        vec3_t transformed_vertices[3];

        //looppa tutti i vertici di questa faccia e applica la trasformazione 
        for (int j = 0; j < 3; j++) {

            vec3_t transformed_vertex = face_vertices[j];

            transformed_vertex = vec3_rotate_y(transformed_vertex, mesh.rotation.y);
            transformed_vertex = vec3_rotate_x(transformed_vertex, mesh.rotation.x);
            transformed_vertex = vec3_rotate_z(transformed_vertex, mesh.rotation.z);

            //sposta il vertice lontano dalla camera 
            transformed_vertex.z -= -5;
            transformed_vertex.y -= -0;

            transformed_vertices[j] = transformed_vertex;
        }

        //TODO> FAI CHECK DI BACKFACE CULLING 

        vec3_t vector_a = transformed_vertices[0];//    A     //
        vec3_t vector_b = transformed_vertices[1];//   / \    //
        vec3_t vector_c = transformed_vertices[2];//  C---B   //

        vec3_t vector_ab = vec3_subtract(vector_b, vector_a);
        vec3_t vector_ac = vec3_subtract(vector_c, vector_a);

        vec3_normalize(&vector_ab);
        vec3_normalize(&vector_ac);

        vec3_t face_normal = vec3_cross_product(vector_ab, vector_ac);

        //va normalizzata la face normal 
        vec3_normalize(&face_normal);

        vec3_t camera_ray = vec3_subtract(camera_position, vector_a);

        float dot_normal_camera = vec3_dot_product(face_normal, camera_ray);

        if (dot_normal_camera < 0) { //i triangoli che non sono verso la camera fanculo
            continue; //lascia fare per questo ciclo e passa al prossimo del for loop 
        }

        //fai ciclo per proiezione solo delle facce che sono frontface  
        for (int j = 0; j < 3; j++) {

               //ritrasformi in 2d e lo proietti il vertice 
            vec2_t projected_point = project(transformed_vertices[j]);


            //SCALA E TRASLA VERSO IL CENTRO DELLO SCHERMO 
            projected_point.x += (window_width / 2);
            projected_point.y += (window_height / 2);

            projected_triangle.points[j] = projected_point;
        }
        //salva il triangolo proiettatoo nell'array di triangoli da renderizzare 
        
        array_push(triangles_to_render, projected_triangle);
        //triangles_to_render[i] = projected_triangle;
    }
    /*
    for (int i = 0; i < N_POINTS; i++) {
        vec3_t point = cube_points[i];
        vec3_t transformed_point = vec3_rotate_y(point, cube_rotation.y);
        transformed_point = vec3_rotate_x(transformed_point, cube_rotation.x);
        transformed_point = vec3_rotate_z(transformed_point, cube_rotation.z);

        // Move the points away from the camera
        //point.z -= camera_position.z;
        transformed_point.z -= camera_position.z;
       
        // Project the current point
        //vec2_t projected_point = project(point);
        vec2_t projected_point = project(transformed_point);
        // Save the projected 2D vector in the array of projected points
        projected_points[i] = projected_point;
    }*/
}

void render(void) {


    draw_grid();

    int num_triangles = array_length(triangles_to_render);

    // Loop all projected triangles and render them
    for (int i = 0; i < num_triangles; i++) {

        triangle_t triangle = triangles_to_render[i]; 
        draw_filled_triangle(
            triangle.points[0].x,
            triangle.points[0].y,
            triangle.points[1].x,
            triangle.points[1].y,
            triangle.points[2].x,
            triangle.points[2].y,
            0xFF00FF00
        );
        draw_triangle(
            triangle.points[0].x,
            triangle.points[0].y,
            triangle.points[1].x,
            triangle.points[1].y,
            triangle.points[2].x,
            triangle.points[2].y,
            0xFF000000
        );
    }

    // draw_line(800,800, 100, 700, 0xFF00FF00);

   // draw_filled_triangle(300, 100, 50, 400, 500, 700, 0xFF00FF00);
    
    //pulisici il buffer array per questo frame 

    array_free(triangles_to_render);

    render_color_buffer();

    clear_color_buffer(0xFF000000);

    SDL_RenderPresent(renderer);
}


//libera le risorse allocate
void    free_resources(void) {
    free(color_buffer);
    array_free(mesh.faces);
    array_free(mesh.vertices);

}

int main(void) {
    is_running = initialize_window();

    setup();
    mesh.rotation.x += 550.00;
    

    while (is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();
    free_resources();

int main(int argc, char**argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	printf("hello World!\n");
	return 0;
}
