/*
 * DecorationShapes.c
 *
 *  Created on: May 12, 2021
 *      Author: divya
 */

#include "DecorationShapes.h"
#include "globals.h"
#define LAMBDA 0.6
#define CLK 0.52

void drawPixel3D(point3D* p0, uint32_t color){
	point2D physical_point[1];
	point3D three_d_points[1];
	three_d_points[0] = *p0;
	convert3Dto2Dpoints( physical_point, three_d_points, 1 );

	drawPixel(physical_point[0].x, physical_point[0].y, color);
}
void drawLine3D(point3D* p0, point3D* p1, uint32_t color){
	point2D physical_point[2];
	point3D three_d_points[2];
	three_d_points[0] = *p0;
	three_d_points[1] = *p1;
	convert3Dto2Dpoints(physical_point, three_d_points, 2);
	drawLine(physical_point[0].x,
			physical_point[0].y,
			physical_point[1].x,
			physical_point[1].y, color);
}
void drawLine3D_jaadu(point3D* p0, point3D* p1, uint32_t color){
	point2D physical_point[2];
	point3D three_d_points[2];

	// magic starts here
	three_d_points[0].z = p0->x;
	three_d_points[0].x = p0->y;
	three_d_points[0].y = p0->z; // constant
	three_d_points[1].z = p1->x;
	three_d_points[1].x = p1->y;
	three_d_points[1].y = p1->z; // constant
	// magic ends here

	convert3Dto2Dpoints(physical_point, three_d_points, 2);
	drawLine(physical_point[0].x,
			physical_point[0].y,
			physical_point[1].x,
			physical_point[1].y, color);
}

void tree_maker3D(float angle, struct tree3D *base_tree, struct tree3D * right_tree, struct tree3D * centre_tree,
		struct tree3D * left_tree){

	left_tree->p0 = base_tree->left_pt;
	left_tree->p1 = branchExtension3D(&(base_tree->reduced_pt), &(base_tree->left_pt), LAMBDA);
	drawLine3D_jaadu(&(left_tree->p0), &(left_tree->p1), GREEN);
	drawHands3D(&(left_tree -> p0), &(left_tree -> p1),LAMBDA, angle, GREEN, &(left_tree->left_pt),&(left_tree->reduced_pt),&(left_tree->right_pt));

	centre_tree->p0 = base_tree->p1;
	centre_tree->p1 = branchExtension3D(&(base_tree->reduced_pt), &(base_tree->p1), LAMBDA);
	drawLine3D_jaadu(&(centre_tree->p0),&(centre_tree->p1), GREEN);
	drawHands3D(&(centre_tree -> p0), &(centre_tree -> p1),LAMBDA, angle, GREEN, &(centre_tree->left_pt),&(centre_tree->reduced_pt),&(centre_tree->right_pt));

	right_tree->p0 = base_tree->right_pt;
	right_tree->p1 = branchExtension3D(&(base_tree->reduced_pt), &(base_tree->right_pt), LAMBDA);
	drawLine3D_jaadu(&(right_tree->p0),&(right_tree->p1), GREEN);
	drawHands3D(&(right_tree -> p0), &(right_tree -> p1),LAMBDA, angle, GREEN, &(right_tree->left_pt),&(right_tree->reduced_pt),&(right_tree->right_pt));

}

void draw_complete_tree_3d(point3D p0, point3D p1)
{
	int variance = 10*3.14/180;
	float rand_angle = CLK;// + rand()%(variance*2) - variance;

	point3D p1_left, p1_right, reduced_point, temp1,  temp2,  temp3,  temp4,  temp5,  temp6;
	drawLine3D_jaadu(&p0,&p1,BROWN);
	drawHands3D(&p0,&p1,LAMBDA, rand_angle, BROWN, &p1_left, &reduced_point,&p1_right);

	struct tree3D base_tree;
    base_tree.p0= p0;
    base_tree.p1= p1;
    base_tree.right_pt = p1_right;
	base_tree.left_pt = p1_left;
	base_tree.reduced_pt= reduced_point;

	int max = 200;
	struct tree3D tree_array[max]; // 3^10
	tree_array[0]=base_tree;
	for(int i =0, j = 1; i<max && j <max; i++){
	tree_maker3D(rand_angle, tree_array + i, tree_array+j, tree_array+j+1, tree_array+j+2);
	j += 3;
	}
}

void drawHands3D(point3D *p0,point3D  *p1, float lambda, float angle, uint32_t color,
		point3D  *p1_left, point3D  *reduced_point,point3D  *p1_right){
	// draw right branch
	calculateBranchEnds3D(p0, p1 ,angle, lambda, reduced_point, p1_right);
	drawLine3D_jaadu(reduced_point,p1_right, color);

	// draw left branch
	calculateBranchEnds3D(p0, p1 ,-angle, lambda, reduced_point, p1_left);
	drawLine3D_jaadu(reduced_point,p1_left, color);
}


void calculateBranchEnds3D(const point3D* p1,const point3D* p2, float branch_angle,
		float lambda, point3D* reduced_point, point3D* rotated_point)
{

	point3D pseudo_origin;
	point3D pt1_wrt_pseudo_origin;
	point3D rotated_pt_wrt_pseudo_origin;
	point3D rotated_pt_wrt_normal_origin;

	//Create Branch
	branchReduction3D(p1, p2, lambda, &pseudo_origin);
	preProcessing3D(p2, &pseudo_origin, &pt1_wrt_pseudo_origin);
	Rotation3D(&pt1_wrt_pseudo_origin, branch_angle, &rotated_pt_wrt_pseudo_origin);
	postProcessing3D(&rotated_pt_wrt_pseudo_origin,  &pseudo_origin, &rotated_pt_wrt_normal_origin);

	//child branch origin = parent branch head
	reduced_point->x = pseudo_origin.x;
	reduced_point->y = pseudo_origin.y;
	reduced_point->z = pseudo_origin.z;
	rotated_point->x = rotated_pt_wrt_normal_origin.x;
	rotated_point->y = rotated_pt_wrt_normal_origin.y;
	rotated_point->z = rotated_pt_wrt_normal_origin.z;
}


void branchReduction3D(point3D* p0, point3D* p1, float lambda, point3D* temp )
{
	temp->x = p0->x + lambda * (p1->x - p0->x);
	temp->y = p0->y + lambda * (p1->y - p0->y);
	temp->z = p0->z + lambda * (p1->z - p0->z);
}

point3D branchExtension3D(point3D* p0, point3D* p1, float lambda)
{
	point3D output;
	lambda = 1;
	output.x = p1->x + (lambda) * (p1->x - p0->x);
	output.y = p1->y + (lambda) * (p1->y - p0->y);
	output.z = p1->z + (lambda) * (p1->z - p0->z);
	return output;
}

void preProcessing3D(const point3D* p0, const point3D* delta, point3D* output)
{
	output->x = p0->x - delta->x;
	output->y = p0->y - delta->y;
	output->z = p0->z - delta->z;

}

void Rotation3D(const point3D* p0, float alpha, point3D* output)
{
	output->x = cos(alpha) * p0->x - sin(alpha) * p0->y;
	output->y = sin(alpha) * p0->x + cos(alpha) * p0->y;
	output->z = p0->z; // TODO

}

void postProcessing3D(const point3D* p0,const point3D* delta, point3D* output)
{
	output->x = p0->x + delta->x;
	output->y = p0->y + delta->y;
	output->z = p0->z + delta->z;

}
