/*
 * structures.h
 *
 *  Created on: May 12, 2021
 *      Author: divya
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

//typedef struct{
//	float x;
//	float y;
//}diffusedReflection;

typedef struct
{
	int x;
	int y;
}point2D;

typedef struct
{
	point2D point_2d;
	float diffused_reflection;
}point2D_DR;

typedef struct
{
	int x;
	int y;
	int z;
} point3D;

typedef struct{
	point2D* point;
	int size;
}line;

typedef struct{
	line* edge;
	int size;
	point2D* vertex;
}polygon;


typedef struct{
	float r;
	float g;
	float b;
}RGBdiffusedReflection;

typedef struct{
	float r;
	float g;
	float b;
}RGBreflectivity;

typedef struct
{
	float sin_THETA ;
	float cos_THETA ;
	float sin_PHI ;
	float cos_PHI ;
	float RHO ;
	float XY_HYPOTENOUS;
}transformationMatrix;

#endif /* STRUCTURES_H_ */
