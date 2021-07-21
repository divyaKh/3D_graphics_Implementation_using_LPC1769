/*
 * globals.c
 *
 *  Created on: May 15, 2021
 *      Author: divya
 */
#include "globals.h"

const int PORT_NUM = 0;
const int ST7735_TFTWIDTH = 127;
const int ST7735_TFTHEIGHT = 159;
const int FOCAL_LENGTH_D = 100;
const point3D VIRTUAL_CAMERA = {200, 200, 200};
const point3D POINT_LIGHT_SOURCE = {60, 60, 200};
//const point3D POINT_LIGHT_SOURCE = {60, 20, 200};
const point3D NORMAL_VECTOR = {0, 0, 1};
//const int LAMBDA = 0.6;
//const int CLK = 0.52;


//----DONOT CHANGE---------//
/* These are chosen very wisely so that when you compute diffused reflection we get the value in
 * the red spectrum and nearby. Since we are considering the reflectivity of 'r' as non zero, we wish to
 * see colours in its range only
 * */

const float SCALING_FACTOR = 20000;
const float OFFSET = 20;
//const float SCALING_FACTOR = 25000;
//const float OFFSET = 0.2;
const RGBreflectivity REFLECTIVITY_R = {0.8, 0, 0};
const RGBreflectivity REFLECTIVITY_G = {0, 0.8, 0};
const RGBreflectivity REFLECTIVITY_B = {0, 0, 0.8};
