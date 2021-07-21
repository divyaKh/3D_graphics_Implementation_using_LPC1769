/*
===============================================================================
 Name        : Divya_Lab3D_CMPE240.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifndef LAB3D_H_
#define LAB3D_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "colors.h"
#include "drawLine.h"
#include "DecorationShapes.h"
#include "structures.h"
#include "globals.h"



//-----------------------------------------------------------
// Projecting 3D points on the 2D display
//-----------------------------------------------------------




float maximum(const float a, const float b);
float calculateDiffusedReflection(const point3D normal_vector, const int reflectivity, const point3D point_light_source,
		const point3D surface_point);

/*
 * @param: 3D virtual camera coordinates
 * @param: pointer to array of points from the World Coordinate system
 * @param: size of array of points from the World Coordinate system
 * @return: null
 * */
//void drawRGBaxis(const point3D virtual_camera, const point3D *world_coordinates, const int size, const int focal_length,
//		const int tft_width, const int tft_height);
void drawRGBaxis(const point3D* axis_coordinates);


/*
 * @param:
 * @param:
 * @param:
 * @param:
 * @return:
 * */
void drawCube(const point3D* Vertex_cube, const int size, uint32_t color);


/*
 * @param:
 * @param:
 * @param:
 * @return:
 * */
void makeShadow( const point3D *Vertices_surface, const int size, const point3D normal_vector,
	const point3D arbritary_point, uint32_t color );

/*
 * @param:
 * @param:
 * @param:
 * @param:
 * @return:
 * */
float findLambda( const point3D surface_vertex, const point3D normal_vector, const point3D arbritary_point );
/*
 * @param:
 * @param:
 * @return:
 * */
point3D findinstersectionPointin3D( const point3D surface_vertex, float lambda );

/*
 * @param: virtual camera coordinates
 * @return struct of transformation matrix
 * */
transformationMatrix determineTranformationMatrix();

/*
 * @param: point from the World Coordinate system
 * @param: transformation matrix struct
 * @return: point in the viewer coordinate system
 * */
point3D convertWorldCoordinatesToViewerCoordinates(const point3D Pw, const transformationMatrix t_matrix);

/*
 * @param: point in the viewer coordinate system
 * @return: projected point in virtual 2D display
 * */
point2D convertViewerCoordinatesToProjectedCoordinates(const point3D Pv);

/*
 * @param: 2D projected point in virtual coordinate system
 * @param: width of the TFT LCD display
 * @param: height of the TFT LCD display
 * @return: point in physical 2D display
 * */
point2D convertVirtualCoordinatesToPhysicalCoordinates(const point2D projected_point);

/*
 * @param: point from the World Coordinate system
 * @param: transformation matrix struct
 * @param: point in the viewer coordinate system
 * */
point2D ThreeDTransformationPipelining(const point3D Pw, const transformationMatrix t_matrix);


void convert3Dto2Dpoints(point2D* physical_point, const point3D *three_d_points, const int size);

void printPoint2D(point2D point);
void printPoint3D(point3D point);
void printTranformationMatrix(transformationMatrix t_matrix);

void* pointsOnALine(line* l, const point2D start_pt, const point2D end_pt);
void fillPolygon(polygon* my_polygon, const uint32_t color);
void colorAnyPolygon(const point3D normal_vector, const point3D arbritary_point, const point3D *Vertices_surface,
		const int size, const uint32_t color);

float diffusedReflectionOfPointCoordinate(const int start_pt_coordinate, const int end_pt_coordinate,
		const int arbitrary_point_coordinate, float start_pt_diffused_reflection, float end_pt_diffused_reflection);

RGBdiffusedReflection diffusedReflectionOfPointOnALine(const point2D start_pt, const point2D end_pt,
		const point2D arbitrary_point, RGBdiffusedReflection start_pt_diffused_reflection,
		RGBdiffusedReflection end_pt_diffused_reflection);

float diffusedReflectionIntermediatePointOneColor(const point2D start_pt, const point2D end_pt, const point2D arbitrary_point,
	float start_pt_diffused_reflection,  float end_pt_diffused_reflection);

float diffusedReflectionVertexForOneColor(const point3D normal_vector, const float reflectivity, const point3D surface_point);

RGBdiffusedReflection diffusedReflectionVertexForRGBColors(const point3D normal_vector,const RGBreflectivity reflectivity,
		const point3D surface_point);

void fillPolygonGradient(const point3D* surface_points, const int size, const point3D normal_vector,
		const RGBreflectivity reflectivity);

void fillaInteriorLineWithGradient(const line* l, const point2D start_pt, const point2D end_pt,
	const RGBdiffusedReflection start_pt_diffused_reflection, const RGBdiffusedReflection end_pt_diffused_reflection);

void fillaBoundaryLineWithGradient(RGBdiffusedReflection* point_Id, const line* l, const point2D start_pt, const point2D end_pt,
	const RGBdiffusedReflection start_pt_diffused_reflection, const RGBdiffusedReflection end_pt_diffused_reflection);

uint32_t findcolor(RGBdiffusedReflection Id);

//-----------------------------------------------------------
// Functions to perform basic operations on 3D vectors
//-----------------------------------------------------------

float dotProduct(point3D p1, point3D p2);
float modulus(point3D p1);
point3D subtract(point3D p1, point3D p2);
float round_value(float v);

#endif //LAB3D_H_
