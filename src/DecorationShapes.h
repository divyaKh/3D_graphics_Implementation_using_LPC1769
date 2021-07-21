#ifndef DECORATION_SHAPES_H_
#define DECORATION_SHAPES_H_

#include "colors.h"
#include "drawLine.h"
#include "structures.h"

//-----------------------------------------------------------
// Code for tree generation
//-----------------------------------------------------------


struct tree{
  point2D p0, p1, right_pt, left_pt, reduced_pt;
};

struct tree3D{
  point3D p0, p1, right_pt, left_pt, reduced_pt;
};


void draw_complete_tree_3d(point3D p0, point3D p1);


void drawHands3D(point3D *p0,point3D  *p1, float lambda, float angle, uint32_t color,
		point3D  *p1_left, point3D  *reduced_point,point3D  *p1_right);


void tree_maker3D(float angle, struct tree3D *base_tree, struct tree3D * right_tree, struct tree3D * centre_tree,
		struct tree3D * left_tree);


void calculateBranchEnds3D(const point3D* p1,const point3D* p2, float branch_angle,
		float lambda, point3D* reduced_point, point3D* rotated_point);

point3D branchExtension3D(point3D* p0, point3D* p1, float lambda);

void branchReduction3D(point3D* p0, point3D* p1, float lambda, point3D* temp );


void preProcessing3D(const point3D* p0, const point3D* delta, point3D* output);

void Rotation3D(const point3D* p0, float alpha, point3D* output);

void postProcessing3D(const point3D* p0,const point3D* delta, point3D* output);

void drawLine3D(point3D* p0, point3D* p1, uint32_t color);

void drawPixel3D(point3D* p0, uint32_t color);

#endif //DECORATION_SHAPES_H_

