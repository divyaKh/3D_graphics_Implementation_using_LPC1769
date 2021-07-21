/*
 * main.c
 *
 *  Created on: May 12, 2021
 *      Author: divya
 */

#include "Divya_Lab3D_CMPE240.h"
#include "globals.h"


int main (void){
 uint32_t pnum = PORT_NUM;
 pnum = 0 ;

 if ( pnum == 0 )	 SSP0Init();
 else	puts("Port number is not correct");
 lcd_init();
 fillrect(0, 0, ST7735_TFTWIDTH, ST7735_TFTHEIGHT, LIGHTYELLOW);


 /*point3D Vertex_cube[8] = {{0,100,140}, {0,0,140}, {100,0,140}, {100,100,140},
							 {100,100,40},{0,100,40},{0,0,40},{100,0,40}};
 point3D Vertex_cube[8] = {{0,50,100}, {0,0,100}, {50,0,100}, {50,50,100},
							 {50,50,50},{0,50,50},{0,0,50},{50,0,50}};*/

 int ll = 100;
 int ll_ = 110;
 int _ll = 10;
 int world_pt = 180;
 point3D Pw[4] = {{0, 0, 0},{world_pt, 0, 0},{0, world_pt, 0},{0, 0, world_pt}};

 point3D p1 = {0,ll,ll_};
 point3D p2 = {0,0,ll_};
 point3D p3 = {ll,0,ll_};
 point3D p4 = {ll,ll,ll_};
 point3D p5 = {ll,ll,_ll};
 point3D p6 = {0,ll,_ll};
 point3D p7 = {0,0,_ll};
 point3D p8 = {ll,0,_ll};

 point3D Vertex_cube[8] = {p1, p2, p3, p4, p5, p6, p7, p8};
// point3D Vertex_cube[8] = {{0,ll,ll_}, {0,0,ll_}, {ll,0,ll_}, {ll,ll,ll_},
//								 {ll,ll,_ll},{0,ll,_ll},{0,0,_ll},{ll,0,_ll}};

 point2D physical_vertices_cube[8];
 point3D normal_xy_plane ={0,0,1};
 point3D normal_xz_plane ={0,1,0};
 point3D normal_yz_plane ={1,0,0};
 point3D arbritary_point = {0,0,0};

drawRGBaxis(Pw);



makeShadow( Vertex_cube , 4, normal_xy_plane, arbritary_point, GRAY );
drawCube( Vertex_cube, 8, BLACK);



//COLOR THE TOP FACE OF CUBE
//point3D top_face_cube[4] = {{0,0,ll_}, {0,ll,ll_}, {ll,ll,ll_}, {ll,0,ll_}};
point3D top_face_cube[4] = {p1, p2, p3, p4};
//colorAnyPolygon(normal_xy_plane, arbritary_point, top_face_cube , 4, RED);
fillPolygonGradient(top_face_cube, 4, normal_xy_plane, REFLECTIVITY_R);

//COLOR THE FRONTAL FACE (RIGHT) OF CUBE
point3D right_frontal_face_cube[4] = {p5, p6, p1, p4};
//colorAnyPolygon( normal_xz_plane, arbritary_point, right_frontal_face_cube , 4 ,LIGHTYELLOW );
fillPolygonGradient(right_frontal_face_cube, 4, normal_xz_plane, REFLECTIVITY_B);

//COLOR THE FRONTAL FACE (LEFT) OF CUBE
point3D left_frontal_face_cube[4] = {p3, p4, p5, p8};
//point3D left_frontal_face_cube[4] = {p5, p4, p3, p8};

//colorAnyPolygon(normal_yz_plane, arbritary_point, left_frontal_face_cube, 4, GREEN );
fillPolygonGradient(left_frontal_face_cube, 4, normal_yz_plane, REFLECTIVITY_G);

// ---------------------
//      create tree
//----------------------
 point3D root = {0.1*ll_, 0.5*ll, ll};
 point3D head = {0.6*ll_, 0.5*ll,ll};
//point3D root = {0.5*ll, ll, 0.1*ll_};
//point3D head = {0.5*ll ,ll, 0.6*ll_};

 draw_complete_tree_3d(root, head);

// ----------------------
//      create letter D
// ----------------------

 point3D outer_D[6] = {{ll, 0.2*ll, 0.2*ll_}
 	 	 	 	 	  ,{ll, 0.2*ll, 0.9*ll_}
 	 	 	 	 	  ,{ll, 0.7*ll, 0.8*ll_}
 	 	 	 	 	  ,{ll, 0.8*ll, 0.7*ll_}
 	 	 	 	 	  ,{ll, 0.8*ll, 0.4*ll_}
 	 	 	 	 	  ,{ll, 0.7*ll, 0.3*ll_}};

 point3D inner_D[6] = {{ll, 0.3*ll, 0.3*ll_}
 	 	 	 	 	  ,{ll, 0.3*ll, 0.8*ll_}
 	 	 	 	 	  ,{ll, 0.6*ll, 0.7*ll_}
 	 	 	 	 	  ,{ll, 0.7*ll, 0.6*ll_}
 	 	 	 	 	  ,{ll, 0.7*ll, 0.5*ll_}
 	 	 	 	 	  ,{ll, 0.6*ll, 0.4*ll_}};
 for(int i = 0; i < 5; i++ ){
	 drawLine3D(outer_D+i, outer_D+i+1, WHITE);
	 drawLine3D(inner_D+i, inner_D+i+1, WHITE);
 }
 drawLine3D(outer_D+5, outer_D, WHITE);
 drawLine3D(inner_D+5, inner_D, WHITE);


 // ----------------------
 //      create letter V
 // ----------------------

// point3D V[6] = {{0.5*ll, ll, 0.2*ll_}
// 	 	 	  ,{0.2*ll, ll, 0.9*ll_}
//			  ,{0.3*ll, ll, 0.9*ll_}
// 	 	 	  ,{0.5*ll, ll, 0.3*ll_}
//			  ,{0.7*ll, ll, 0.9*ll_}
//			  ,{0.8*ll, ll, 0.9*ll_}};

 point3D V[6] = {{0.5*ll, 0.2*ll, ll_}
 	 	 	  ,{0.2*ll, 0.9*ll, ll_}
			  ,{0.3*ll, 0.9*ll, ll_}
 	 	 	  ,{0.5*ll, 0.3*ll, ll_}
			  ,{0.7*ll, 0.9*ll, ll_}
			  ,{0.8*ll, 0.9*ll, ll_}};

 for(int i = 0; i < 5; i++ ){
	 drawLine3D(V+i, V+i+1, WHITE);
 }
 drawLine3D(V+5, V, WHITE);








 return 0;
}

