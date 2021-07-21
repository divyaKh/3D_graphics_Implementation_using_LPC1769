
#include "Divya_Lab3D_CMPE240.h"
#include <stdio.h>

//------------------ Diffused reflection of the vertices of desired surface- Id (r,g,b)  ----------------//

RGBdiffusedReflection diffusedReflectionVertexForRGBColors(const point3D normal_vector,const RGBreflectivity reflectivity,
		const point3D surface_point){
	RGBdiffusedReflection Id;
	Id.r = diffusedReflectionVertexForOneColor( normal_vector, reflectivity.r, surface_point );
	Id.g =diffusedReflectionVertexForOneColor( normal_vector, reflectivity.g, surface_point );
	Id.b =diffusedReflectionVertexForOneColor( normal_vector, reflectivity.b, surface_point );
	return Id;
}

float diffusedReflectionVertexForOneColor(const point3D normal_vector, const float reflectivity,
		const point3D surface_point){
	float diffused_reflection, angle;
	point3D ray = subtract(POINT_LIGHT_SOURCE,surface_point);
	angle = dotProduct(normal_vector,ray) / (modulus(ray) * modulus(normal_vector));
	diffused_reflection = angle / pow(modulus(ray),2);
	diffused_reflection = diffused_reflection * SCALING_FACTOR + OFFSET;
	return reflectivity * diffused_reflection;
}

//------------------ Fill a ploygon with Gradient colours  ----------------//

void fillPolygonGradient(const point3D* vertices_surface, const int size, const point3D normal_vector,
		const RGBreflectivity reflectivity){

//-----------diffused Reflection For Vertices--------------------//
	RGBdiffusedReflection Id[4];
	uint32_t color[4];
	for(int i = 0; i < 4; i++){
		Id[i] = diffusedReflectionVertexForRGBColors(normal_vector, reflectivity, vertices_surface[i]);
		color[i] = findcolor(Id[i]);
		drawPixel3D( vertices_surface + i, color[i]);
	}

//-----------colour the boundary points of a polygon--------------------------//
	point2D physical_vertices[size];
	line shape_edges[size];
	RGBdiffusedReflection point_Id;
	uint32_t temp_color;
	convert3Dto2Dpoints(physical_vertices, vertices_surface, size);
	//-----------colour the entire polygon with gradient--------------------------//

		polygon face_polygon;
		face_polygon.size = size;
		//allocating size to pointer of a line
		face_polygon.edge = (line*) malloc(sizeof(int) + sizeof(point2D*));
		face_polygon.edge->point = (point2D*) malloc(2 * sizeof(int));
		face_polygon.vertex = physical_vertices;
		gradientUsingDDA(&face_polygon, Id, size);

//	for(int i = 0 ; i < size-1 ; i++){
//		pointsOnALine(shape_edges+i , physical_vertices[i], physical_vertices[i+1]);
//		fillaLineWithGradient(shape_edges+i, physical_vertices[i], physical_vertices[i+1], Id[i], Id[i+1]);
//	}
//	pointsOnALine(shape_edges+size-1 , physical_vertices[size-1], physical_vertices[0]);
//	fillaLineWithGradient(shape_edges+size-1, physical_vertices[size-1], physical_vertices[0], Id[size-1], Id[0]);
}

uint32_t findcolor(RGBdiffusedReflection Id){
	uint32_t color = 0;
	float red,  green, blue;
	red	= (255 * Id.r);
	green = (255 * Id.g);
	blue = (255 * Id.b);
	color =	(((uint32_t)red) << 16) | (((uint32_t)green) << 8) | ((uint32_t)blue);
	return color;
}

//yeh poitns on line bhar ke deta hai
void fillaBoundaryLineWithGradient(RGBdiffusedReflection* point_Id, const line* l, const point2D start_pt, const point2D end_pt,
	const RGBdiffusedReflection start_pt_diffused_reflection, const RGBdiffusedReflection end_pt_diffused_reflection){
	uint32_t temp_color;

	for(int i = 0; i < l->size ; i++ ){
		point_Id[i] = diffusedReflectionOfPointOnALine(start_pt, end_pt,
			l->point[i], start_pt_diffused_reflection, end_pt_diffused_reflection);
		temp_color = findcolor(point_Id[i]);
		drawPixel( l->point[i].x , l->point[i].y , temp_color);
	}
}

//yeh points on line bhar ke nh deta
void fillaInteriorLineWithGradient(const line* l, const point2D start_pt, const point2D end_pt,
	const RGBdiffusedReflection start_pt_diffused_reflection, const RGBdiffusedReflection end_pt_diffused_reflection){
	uint32_t temp_color;
	RGBdiffusedReflection point_Id;
	for(int i = 0; i < l->size ; i++ ){
		point_Id = diffusedReflectionOfPointOnALine(start_pt, end_pt,
			l->point[i], start_pt_diffused_reflection, end_pt_diffused_reflection);
		temp_color = findcolor(point_Id);
		drawPixel( l->point[i].x , l->point[i].y , temp_color);
	}
}

//void fillaLineWithGradient(RGBdiffusedReflection* point_Id, const line* l, const point2D start_pt, const point2D end_pt,
//	const RGBdiffusedReflection start_pt_diffused_reflection, const RGBdiffusedReflection end_pt_diffused_reflection){
//	uint32_t temp_color;
//
//	for(int i = 0; i < l->size ; i++ ){
//		point_Id[i] = diffusedReflectionOfPointOnALine(start_pt, end_pt,
//			l->point[i], start_pt_diffused_reflection, end_pt_diffused_reflection);
//		temp_color = findcolor(point_Id[i]);
//		drawPixel( l->point[i].x , l->point[i].y , temp_color);
//	}
//}


//-------------------- Diffused reflection of any point on a boundary line  -----------------------------------//


RGBdiffusedReflection diffusedReflectionOfPointOnALine(const point2D start_pt, const point2D end_pt,
		const point2D arbitrary_point, RGBdiffusedReflection start_pt_diffused_reflection,
		RGBdiffusedReflection end_pt_diffused_reflection){
	RGBdiffusedReflection Id;
	Id.r = diffusedReflectionIntermediatePointOneColor(start_pt, end_pt, arbitrary_point, start_pt_diffused_reflection.r ,
		end_pt_diffused_reflection.r);
	Id.g = diffusedReflectionIntermediatePointOneColor(start_pt, end_pt, arbitrary_point, start_pt_diffused_reflection.g,
		end_pt_diffused_reflection.g);
	Id.b = diffusedReflectionIntermediatePointOneColor(start_pt, end_pt, arbitrary_point, start_pt_diffused_reflection.b ,
		end_pt_diffused_reflection.b);
	return Id;
}

float diffusedReflectionIntermediatePointOneColor(const point2D start_pt, const point2D end_pt, const point2D arbitrary_point,
	float start_pt_diffused_reflection,  float end_pt_diffused_reflection){
	float Idx, Idy;
	Idx = diffusedReflectionOfPointCoordinate(start_pt.x, end_pt.x, arbitrary_point.x,
			start_pt_diffused_reflection, end_pt_diffused_reflection);
	Idy = diffusedReflectionOfPointCoordinate(start_pt.y, end_pt.y, arbitrary_point.y,
			start_pt_diffused_reflection, end_pt_diffused_reflection);
	 return 0.5 * (Idx + Idy);
}

float diffusedReflectionOfPointCoordinate(const int start_pt_coordinate, const int end_pt_coordinate,
		const int arbitrary_point_coordinate, float start_pt_diffused_reflection, float end_pt_diffused_reflection){
	float exp1, exp2, exp3;
	exp1 = start_pt_diffused_reflection - end_pt_diffused_reflection;
	exp2 = (arbitrary_point_coordinate - end_pt_coordinate) / (start_pt_coordinate - end_pt_coordinate);
	exp3 = end_pt_diffused_reflection;
	return exp1*exp2 + exp3;
}

//-------------------- DDA algorithm to calculate all points on a line and color them -----------------------------------//

void* pointsOnALine(line* l, const point2D start_pt, const point2D end_pt){
	double delta_x, delta_y, number_of_steps;
	float increment_x, increment_y;
	float curr_pt_x = start_pt.x;
	float curr_pt_y = start_pt.y;
	delta_x =  (end_pt.x - start_pt.x);
	delta_y =  (end_pt.y - start_pt.y);

	number_of_steps = maximum(abs(delta_x), abs(delta_y));
	l->size = (int)number_of_steps;

	//dynamically allocating memory to store points in a line
	l->point = malloc(l->size * sizeof(point2D));

	increment_x = delta_x / (float)number_of_steps;
	increment_y = delta_y / (float)number_of_steps;

	//Each iteration calculates next point on line
	for(int i = 0; i < l->size  ; i++ ){
		curr_pt_x += increment_x;
		curr_pt_y += increment_y;
		l->point[i].x = (int) round_value(curr_pt_x);
		l->point[i].y = (int) round_value(curr_pt_y);
	}
	return l->point;
}

//-------------colour a polygon using  Scanning line and DDA algorithm-------------------//

void fillPolygon(polygon *my_polygon, const uint32_t color){
	int poly_size = my_polygon -> size;
	point2D start_pt, end_pt;
	line scanning_line;
	int first_edge_size;

	//-----calculate points of first 2 edges-----//
	void* free_karne_waali_line[2];
	for(int i = 0 ; i < poly_size/2 ; i++){
		free_karne_waali_line[i] = pointsOnALine(my_polygon->edge+i, my_polygon -> vertex[i],
				my_polygon -> vertex[i+1]);
		fillaLine(my_polygon->edge+i, color);
	}

	first_edge_size = my_polygon->edge[0].size;
	void* temp;
	for(int j = 0 ; j < first_edge_size ; j++){
		start_pt = my_polygon -> edge[0].point[first_edge_size-j-1];
		end_pt = my_polygon -> edge[1].point[j];
		temp = pointsOnALine(&scanning_line, start_pt, end_pt);
		fillaLine(&scanning_line, color);
		free(temp);
	}
	free(free_karne_waali_line[0]);
	free(free_karne_waali_line[1]);
	free(my_polygon -> edge);
	free(my_polygon -> edge+1);

	//points of 3rd and 4th edge
	void* free_karne_waali_line2[2];
	free_karne_waali_line2[0]=pointsOnALine(my_polygon->edge + 2, my_polygon -> vertex[2],
			my_polygon -> vertex[3]);
	fillaLine(my_polygon ->edge + 2, color);
	free_karne_waali_line2[1]=pointsOnALine(my_polygon->edge+poly_size-1, my_polygon -> vertex[poly_size-1],
				  my_polygon -> vertex[0]);
	fillaLine(my_polygon ->edge + poly_size-1, color);


	first_edge_size = my_polygon->edge[2].size;
	int second_edge_size = my_polygon->edge[3].size;
	for(int j = 0 ; j < first_edge_size ; j++){
		start_pt = my_polygon -> edge[2].point[j];
		end_pt = my_polygon -> edge[3].point[my_polygon->edge[2].size - j -1];
		temp = pointsOnALine(&scanning_line, start_pt, end_pt);
		fillaLine(&scanning_line, color);
		free(temp);
	}

	free(free_karne_waali_line2[0]);
	free(free_karne_waali_line2[1]);
	free(my_polygon -> edge + 2);
	free(my_polygon -> edge + 3);

}

void fillaLine(const line* l, uint32_t color){
	for(int i = 0; i < l->size ; i++ ){
			drawPixel( l->point[i].x , l->point[i].y , color);
	}
}

float maximum(const float a, const float b){
	if(b > a) return b;
	else return a;
}

float round_value(float v){
  return floor(v + 0.5);
}

//-------------------- Make coloured shadow of surface of cube -----------------------------------//

void makeShadow( const point3D *Vertices_surface, const int size, const point3D normal_vector,
	const point3D arbritary_point, uint32_t color ){
	float lambda[size];
	point3D intersection_point[size];
	point2D physical_instersection_points[size];

//	printf("Following are the shadow points: \n");
	for(int i = 0; i < size; i++){
		lambda[i] = findLambda(Vertices_surface[i], normal_vector, arbritary_point);
		intersection_point[i] = findinstersectionPointin3D(Vertices_surface[i],lambda[i]);
	}
	for(int i = 0 ; i < size-1 ; i++){
		drawLine3D(intersection_point + i,intersection_point + i + 1,BLACK);
	}
	drawLine3D(intersection_point + size - 1, intersection_point,BLACK);
	printPoint3D(intersection_point[0]);
		printPoint3D(intersection_point[1]);
		printPoint3D(intersection_point[2]);
		printPoint3D(intersection_point[3]);
	//fetch the physical coordinates of shadow to use to fill it
	convert3Dto2Dpoints(physical_instersection_points, intersection_point, size);
	polygon shadow_polygon;
	shadow_polygon.size = size;

	//allocating size to pointer of a line
	shadow_polygon.edge = (line*) malloc(sizeof(int) + sizeof(point2D*));
	shadow_polygon.edge->point = (point2D*) malloc(2 * sizeof(int));
	shadow_polygon.vertex = physical_instersection_points;

	fillPolygon(&shadow_polygon, color);

}

void gradientUsingDDA(polygon *my_polygon, RGBdiffusedReflection* Id, int size){
	int poly_size = my_polygon -> size;
	point2D start_pt, end_pt;
	line scanning_line;
	int first_edge_size;
	RGBdiffusedReflection* point_Id[2];

	//-----calculate points of first 2 edges-----//
	void* free_karne_waali_line[2];
	for(int i = 0 ; i < poly_size/2 ; i++){
		free_karne_waali_line[i] = pointsOnALine(my_polygon->edge+i, my_polygon -> vertex[i],
				my_polygon -> vertex[i+1]);
		point_Id[i] = (RGBdiffusedReflection*) malloc(my_polygon->edge[i].size * 3 * sizeof(float));
		fillaBoundaryLineWithGradient(point_Id[i], my_polygon->edge+i,  my_polygon -> vertex[i], my_polygon -> vertex[i+1],
				 Id[i], Id[i+1]);
	}

	first_edge_size = my_polygon->edge[0].size;
	void* temp;
	for(int j = 0 ; j < first_edge_size ; j++){
		start_pt = my_polygon -> edge[0].point[first_edge_size-j-1];
		end_pt = my_polygon -> edge[1].point[j];
		temp = pointsOnALine(&scanning_line, start_pt, end_pt);
		fillaInteriorLineWithGradient(&scanning_line,  start_pt, end_pt,
				point_Id[0][first_edge_size-j-1], point_Id[1][j]);
		free(temp);
	}
	free(point_Id[0]);
	free(point_Id[1]);
	free(free_karne_waali_line[0]);
	free(free_karne_waali_line[1]);
	free(my_polygon -> edge);
	free(my_polygon -> edge+1);

	//points of 3rd and 4th edge
	void* free_karne_waali_line2[2];
	free_karne_waali_line2[0]=pointsOnALine(my_polygon->edge + 2, my_polygon -> vertex[2],
			my_polygon -> vertex[3]);
	point_Id[0] = (RGBdiffusedReflection*) malloc(my_polygon->edge[2].size * 3 * sizeof(float));
	fillaBoundaryLineWithGradient(point_Id[0], my_polygon->edge+2,  my_polygon -> vertex[2], my_polygon -> vertex[3],
				 Id[2], Id[3]);
	free_karne_waali_line2[1]=pointsOnALine(my_polygon->edge+poly_size-1, my_polygon -> vertex[poly_size-1],
				  my_polygon -> vertex[0]);
	point_Id[1] = (RGBdiffusedReflection*) malloc(my_polygon->edge[poly_size-1].size * 3 * sizeof(float));
	fillaBoundaryLineWithGradient(point_Id[1], my_polygon->edge+poly_size-1,  my_polygon -> vertex[poly_size-1],
			my_polygon -> vertex[0], Id[3], Id[0]);

	first_edge_size = my_polygon->edge[2].size;
	 int second_edge_size = my_polygon->edge[3].size;
	 for(int j = 0 ; j < first_edge_size ; j++){
		start_pt = my_polygon -> edge[2].point[j];
		end_pt = my_polygon -> edge[3].point[my_polygon->edge[2].size - j -1];
		temp = pointsOnALine(&scanning_line, start_pt, end_pt);
		fillaInteriorLineWithGradient(&scanning_line,  start_pt, end_pt, point_Id[0][j],
			point_Id[1][first_edge_size - j -1]);
		free(temp);
	 }
	 free(point_Id[0]);
	 free(point_Id[1]);
	 free(free_karne_waali_line2[0]);
	 free(free_karne_waali_line2[1]);
	 free(my_polygon -> edge + 2);
	 free(my_polygon -> edge + 3);

}

void colorAnyPolygon(const point3D normal_vector, const point3D arbritary_point, const point3D *Vertices_surface,
		const int size, const uint32_t color){

	point2D physical_points[size];
	convert3Dto2Dpoints(physical_points, Vertices_surface, size);

	polygon face_polygon;
	face_polygon.size = size;
	//allocating size to pointer of a line
	face_polygon.edge = (line*) malloc(sizeof(int) + sizeof(point2D*));
	face_polygon.edge->point = (point2D*) malloc(2 * sizeof(int));
	face_polygon.vertex = physical_points;
	fillPolygon(&face_polygon, color);
}


float findLambda( const point3D surface_vertex, const point3D normal_vector, const point3D arbritary_point ){
	float numerator, denominator;
	numerator = normal_vector.x * (arbritary_point.x - POINT_LIGHT_SOURCE.x)
				+ normal_vector.y * (arbritary_point.y - POINT_LIGHT_SOURCE.y)
				+ normal_vector.z * (arbritary_point.z - POINT_LIGHT_SOURCE.z);
	denominator = normal_vector.x * (surface_vertex.x - POINT_LIGHT_SOURCE.x)
				+ normal_vector.y * (surface_vertex.y - POINT_LIGHT_SOURCE.y)
				+ normal_vector.z * (surface_vertex.z - POINT_LIGHT_SOURCE.z);
	return numerator/denominator;
}

point3D findinstersectionPointin3D( const point3D surface_vertex, float lambda ){
	point3D intersection_point;
	intersection_point.x = POINT_LIGHT_SOURCE.x + lambda * (surface_vertex.x - POINT_LIGHT_SOURCE.x);
	intersection_point.y = POINT_LIGHT_SOURCE.y + lambda * (surface_vertex.y - POINT_LIGHT_SOURCE.y);
	intersection_point.z = POINT_LIGHT_SOURCE.z + lambda * (surface_vertex.z - POINT_LIGHT_SOURCE.z);
	return intersection_point;
}

void drawRGBaxis(const point3D* axis_coordinates){
	drawLine3D( axis_coordinates, axis_coordinates+1, RED );
	drawLine3D( axis_coordinates, axis_coordinates+2, GREEN );
	drawLine3D( axis_coordinates, axis_coordinates+3, BLUE );
}
void drawCube(const point3D* Vertex_cube, const int size, uint32_t color){
	//DRAW TOP FACE
	drawLine3D(Vertex_cube,Vertex_cube+1,color);
	drawLine3D(Vertex_cube+1,Vertex_cube+2,color);
	drawLine3D(Vertex_cube+2,Vertex_cube+3,color);
	drawLine3D(Vertex_cube+3,Vertex_cube+0,color);

	//DRAW BOTTOM FACE
	drawLine3D(Vertex_cube+4,Vertex_cube+5,color);
	drawLine3D(Vertex_cube+7,Vertex_cube+4,color);

	//DRAW VERTICAL EDGES
	drawLine3D(Vertex_cube+0,Vertex_cube+5,color);
	drawLine3D(Vertex_cube+2,Vertex_cube+7,color);
	drawLine3D(Vertex_cube+3,Vertex_cube+4,color);
}


void convert3Dto2Dpoints(point2D* physical_point, const point3D *three_d_points, const int size){
	transformationMatrix t_matrix = determineTranformationMatrix();
	 for(int i=0; i<size; i++){
		 physical_point[i] = ThreeDTransformationPipelining(three_d_points[i], t_matrix);
	}
}

point2D ThreeDTransformationPipelining(const point3D Pw, const transformationMatrix t_matrix){
	point2D projected_point, physical_point;
	point3D Pv;
	Pv = convertWorldCoordinatesToViewerCoordinates(Pw, t_matrix);
	projected_point = convertViewerCoordinatesToProjectedCoordinates(Pv);
	physical_point = convertVirtualCoordinatesToPhysicalCoordinates(projected_point);
	return physical_point;
}

transformationMatrix determineTranformationMatrix(){
	transformationMatrix t_matrix;
	//Transformation matrix
	t_matrix.XY_HYPOTENOUS = sqrt (pow(VIRTUAL_CAMERA.x , 2) + pow(VIRTUAL_CAMERA.y , 2));
	t_matrix.RHO = sqrt ( pow(VIRTUAL_CAMERA.x , 2) + pow(VIRTUAL_CAMERA.y , 2) + pow(VIRTUAL_CAMERA.z , 2) );
	t_matrix.sin_THETA = VIRTUAL_CAMERA.y / t_matrix.XY_HYPOTENOUS;
	t_matrix.cos_THETA = VIRTUAL_CAMERA.x / t_matrix.XY_HYPOTENOUS;
	t_matrix.sin_PHI = t_matrix.XY_HYPOTENOUS / t_matrix.RHO;
	t_matrix.cos_PHI = VIRTUAL_CAMERA.z / t_matrix.RHO;
	return t_matrix;
}

point3D convertWorldCoordinatesToViewerCoordinates(const point3D Pw, const transformationMatrix t_matrix){
	point3D Pv;
	Pv.x = (-1 * t_matrix.sin_THETA * Pw.x) + (t_matrix.cos_THETA * Pw.y);
	Pv.y = (-1 * t_matrix.cos_PHI * t_matrix.cos_THETA * Pw.x) + (-1 * t_matrix.cos_PHI * t_matrix.sin_THETA * Pw.y) + (t_matrix.sin_PHI * Pw.z);
	Pv.z = (-1 * t_matrix.sin_PHI * t_matrix.cos_THETA * Pw.x) + (-1 * t_matrix.sin_PHI * t_matrix.cos_THETA * Pw.y) + (-1 * t_matrix.cos_PHI * Pw.z) + (t_matrix.RHO) ;
	return Pv;
}

point2D convertViewerCoordinatesToProjectedCoordinates(const point3D Pv){
	point2D projected_point;
	projected_point.x = FOCAL_LENGTH_D * Pv.x / Pv.z;
	projected_point.y = FOCAL_LENGTH_D * Pv.y / Pv.z ;
	return projected_point;
}


point2D convertVirtualCoordinatesToPhysicalCoordinates(const point2D projected_point){
	point2D physical_point;
	physical_point.x = projected_point.x + (ST7735_TFTWIDTH/2);
	physical_point.y = -projected_point.y + (ST7735_TFTHEIGHT/2);
	return physical_point;
}


float dotProduct(point3D p1, point3D p2){
	return ((p1.x * p2.x) + (p1.y * p2.y) + (p1.z * p2.z));
}

float modulus(point3D p1){
	return sqrt(pow(p1.x,2) + pow(p1.y,2) + pow(p1.z, 2));
}

point3D subtract(point3D p1, point3D p2){
	point3D result;
	result.x = p1.x - p2.x;
	result.y = p1.y - p2.y;
	result.z = p1.z - p2.z;
	return result;
}

void printPoint2D(point2D point){
	printf("{ %d, %d }\n", point.x , point.y);
}

void printPoint3D(point3D point){
	printf("{ %d, %d, %d}\n", point.x , point.y, point.z);
}

void printTranformationMatrix(transformationMatrix t_matrix)
{
	printf("{ RHO, %f }\n", t_matrix.RHO);
	printf("{ sin_THETA:  %f }\n", t_matrix.sin_THETA);
	printf("{ cos_THETA:  %f }\n", t_matrix.cos_THETA);
	printf("{ sin_PHI:  %f }\n", t_matrix.sin_PHI);
	printf("{ cos_PHI: %f }\n", t_matrix.cos_PHI);
}

