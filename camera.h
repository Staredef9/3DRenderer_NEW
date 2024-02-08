#ifndef CAMERA_H
#define CAMERA_H
#include "vectors.h"
typedef struct camera_t {
	vec3_t	position;
	vec3_t	rotation;
	float	fov_angle;
}camera_t;

#endif