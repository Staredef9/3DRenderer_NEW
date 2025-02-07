#include "vectors.h"
#include <math.h>



//IMPLEMENTAZIONE VEC2D FUNZIONI 
float vec2_t_length(vec2_t v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

vec2_t vec2_add(vec2_t a, vec2_t b)
{
	vec2_t result = { .x = a.x + b.x, .y = a.y + b.y };
	return result;
}

vec2_t vec2_subtract(vec2_t a, vec2_t b)
{
	vec2_t result = { .x = a.x - b.x, .y = a.y - b.y };
	return result;
}

vec2_t vec2_multiply(vec2_t a, float factor)
{
	vec2_t result = {.x = a.x * factor, .y = a.y * factor};
	return result;
}

vec2_t vec2_divide(vec2_t a, float factor)
{
	vec2_t result = { .x = a.x / factor, .y = a.y / factor };
	return result;
}

float vec2_dot_product(vec2_t a, vec2_t b)
{
	return (a.x * b.x + a.y * b.y);
}

void vec2_normalize(vec2_t* normal)
{
	float length = vec2_t_length(*normal);
	normal->x = normal->x / length;
	normal->y = normal->y / length;
}

//IMPLEMENTAZIONI VEC3D

float vec3_t_length(vec3_t v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3_t vec3_add(vec3_t a, vec3_t b)
{
	vec3_t result = { .x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
	return result;
}

vec3_t vec3_subtract(vec3_t a, vec3_t b)
{
	vec3_t result = { .x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z };
	return result;
}

vec3_t vec3_multiply(vec3_t a, float factor)
{
	vec3_t result = { .x = a.x * factor, .y = a.y * factor, .z = a.z * factor };
	return result;
}

vec3_t vec3_divide(vec3_t a, float factor)
{
	vec3_t result = { .x = a.x / factor, .y = a.y / factor, .z = a.z / factor };
	return result;
}

vec3_t vec3_cross_product(vec3_t a, vec3_t b)
{
	vec3_t result = {
	.x = (a.y * b.z) - (a.z * b.y),
	.y = (a.z * b.x) - (a.x * b.z),
	.z = (a.x * b.y) - (a.y * b.x)
	};
	return result;
}

float vec3_dot_product(vec3_t a, vec3_t b)
{
	float result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z); 
	return result;
}

void vec3_normalize(vec3_t* normal)
{
	float length = vec3_t_length(*normal);
	normal->x = normal->x / length;
	normal->y = normal->y / length;
	normal->z = normal->z / length;
}

vec3_t vec3_rotate_x(vec3_t v, float angle)
{
	vec3_t rotated_vector = {
		.x = v.x,
		.y = v.y * cos(angle) - v.z * sin(angle),
		.z = v.y * sin(angle) + v.z * cos(angle)
	};
	return rotated_vector;
}
vec3_t vec3_rotate_y(vec3_t v, float angle)
{
	vec3_t rotated_vector = {
		.x = v.x * cos(angle) - v.z * sin(angle),
		.y = v.y,
		.z = v.x * sin(angle) + v.z * cos(angle)
	};
	return rotated_vector;
}
vec3_t vec3_rotate_z(vec3_t v, float angle)
{
	vec3_t rotated_vector = {
		.x = v.x * cos(angle) - v.y * sin(angle),
		.y = v.x * sin(angle) + v.y * cos(angle),
		.z = v.z
	};
	return rotated_vector;
}

vec3_t vec3_from_vec4(vec4_t v)
{
	vec3_t new = { v.x,v.y,v.z };
	return new;
}

vec4_t vec4_from_vec3(vec3_t v)
{
	vec4_t new = { v.x,v.y,v.z,1 };
	return new;
}
