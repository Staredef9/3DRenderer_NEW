#ifndef VECTOR_H
#define VECTOR_H


typedef struct vec2_t {
	float x;
	float y;
}vec2_t;

typedef struct vec3_t {
	float x;
	float y;
	float z;
}vec3_t;

typedef struct vec4_t {
	float x;
	float y;
	float z;
	float w;
} vec4_t;



//VEC2 OPERATIONS 

float vec2_t_length(vec2_t v);

vec2_t vec2_add(vec2_t a, vec2_t b);

vec2_t vec2_subtract(vec2_t a, vec2_t b);

vec2_t vec2_multiply(vec2_t a, float factor);

vec2_t vec2_divide(vec2_t a, float factor);

float vec2_dot_product(vec2_t a, vec2_t b);

void vec2_normalize(vec2_t* normal);


//TO DO aggiungi vec2add, vec2sub, vec2mult, ecc 

//VEC3 OPEERATIONS 

float vec3_t_length(vec3_t v);
//TO DO aggiungi vec3add, vec3sub, vec3mult, ecc 


vec3_t vec3_add(vec3_t a, vec3_t b);

vec3_t vec3_subtract(vec3_t a, vec3_t b);

vec3_t vec3_multiply(vec3_t a, float factor);

vec3_t vec3_divide(vec3_t a, float factor);

vec3_t vec3_cross_product(vec3_t a, vec3_t b);

float vec3_dot_product(vec3_t a, vec3_t b);

void	vec3_normalize(vec3_t* normal);

vec3_t vec3_rotate_x(vec3_t v, float angle);
vec3_t vec3_rotate_y(vec3_t v, float angle);
vec3_t vec3_rotate_z(vec3_t v, float angle);

vec3_t vec3_from_vec4(vec4_t v);


////VEC4 functions

//vector conversion
vec4_t vec4_from_vec3(vec3_t v);




#endif