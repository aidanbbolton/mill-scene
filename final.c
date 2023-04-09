/*
*  Creates and Renders a scene

*  Key Bindings
*  m			Switch between Perspective and first person
*  wads			Move around in First person view
*  arrows       Rotate the scene
*				Rotate the view in First Person
*  +/-      	Changes the FOV
*  i/I			Increases/Decreases ambient value
*  o/O			Increases/Decreases diffuse value
*  p/P			Increases/Decreases specular value
*  c/C			Change the colors to show polygons
*  l			Toggle lighting
*  k			Stop the light from rotating
*  page up/down Move the light
*  0			Reset the view angle
*  ESC			Exit


*/

#include "WGP.h"

int th=0;          //  Azimuth of view angle
int ph=35;          //  Elevation of view angle
double zh=0; 	   //  time
int mode=1;  	   //  Switch between modes
int fov=35;		   //  Field of View
double asp=1;      //  Aspect Ratio
double dim=128;	   //Size of the box
double boardSize=400;
double unit=4;
double Y[100][100];
double Norm[100][100];
double Dep[100][3];
unsigned int texture[5];

//Eye position
double Ex = -60;
double Ey = 10;
double Ez = -50;
//Look at position
double Cx = -60;
double Cy = 10;
double Cz = -45;

//Lighting values
int ambient   =  30;  // Ambient intensity (%)
int diffuse   =  30;  // Diffuse intensity (%)
int specular  =  30;  // Specular intensity (%)
int shiny     =   5;  // Shininess (power of two)
int distance  =  72;  // Light orbit radius
int emission   =   0;
int light = 0;
int stop = 1;

int px = 0;
// int pz = 0;
// int py = 0;
int base=1;
int colors=0;
int shader = 0;

/*
	Storeres norrmal to vector in 3
*/
void Normal(double* P, double* Q, double* R, double* cross) {
				   
	double u[3] = {0,0,0};
	double v[3] = {0,0,0};
	
	for(int i=0;i<3;i++) {
		u[i] = P[i] - Q[i];
		v[i] = R[i] - P[i];
	}
	
	cross[0] = (u[1] * v[2]) - (u[2] *v[1]);
	cross[1] = (u[2] * v[0]) - (u[0] *v[2]);
	cross[2] = (u[0] * v[1]) - (u[1] *v[0]);
				   
}


void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);

   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

void setup() {
	int num;
	for(num=0;num<60;num++) {
	
		if(num>45) {
			Dep[num][0]=36+(num-46)*unit;
			Dep[num][1]=-36-(num-46)*unit;
			Dep[num][2]=9;
	
		} else if (num>34) {
			Dep[num][0]=36;
			Dep[num][1]=-40+(num-35)*unit;
			Dep[num][2]=9;
		} else {
			Dep[num][0]=-124+num*unit;
			Dep[num][1]=30;
			Dep[num][2]=9;
		}
	}
	// //Pond
	Dep[num][0]=-5;
	Dep[num][1]=30;
	Dep[num][2]=30;
	num++;

	Dep[num][0]=30;
	Dep[num][1]=23;
	Dep[num][2]=30;
	num++;

	Dep[num][0]=17;
	Dep[num][1]=13;
	Dep[num][2]=20;
	num++;
	
	
	for(int i=0;i<boardSize/unit;i++) {
		double x=i*unit-boardSize/2;
		for(int j=0;j<boardSize/unit;j++) {
			double z=j*unit-boardSize/2;
			for(int k=0;k<num;k++) {
				
				double d= sqrt(pow(Dep[k][0]-x,2)+pow(Dep[k][1]-z,2));

				
				if(d<Dep[k][2]) {
					Y[i][j]+=(Dep[k][2]-d)*(-1);
				}
			}
			double adj = (rand()%300)/100-1.5;
			Y[i][j] += adj;
		}
	}
	
	for(int i=1;i<boardSize/unit-1;i++) {
		for(int j=1;j<boardSize/unit-1;j++) {
		
			Norm[i][j] = (Y[i-1][j] + Y[i+1][j] + Y[i][j-1]+ Y[i][j+1] + Y[i][j])/5;
		}
	}
	
}
/*
	triangles tries to draw the scene the bells and whistles 
	x -> x coord
	y -> y coord
	z -> z coord
	s -> scale
	rx -> rotation on the x axis
	rz -> rotation on the z axis
	colors -> display textures and colors or not
	tex -> texture number
	ts -> texture scale
	texi -> temporary variable to remember what part of the texture to display.
*/

void triangles(double x, double y, double z, double s,double rx, double rz, 
				int colors, int tex, double ts, int texi) {
				
	double t0 = texi/ts;
	double t1 = (texi+1)/ts;
	
	glPushMatrix();
	
	if(rx) glRotated(rx,1,0,0);
	if(rz) glRotated(rz,0,0,1);
	
	double P[3];
	double Q[3];
	double R[3];
	double S[3];
	double norm[3];
	
	if(!colors) {
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE ,light?GL_REPLACE:GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D,texture[tex]);
	} else {
		glDisable(GL_TEXTURE_2D);
	}
	
	if(base){
	
		int i=(x+boardSize/2)/s;
		int j=(z+boardSize/2)/s;

		P[0] = x;   P[1] = Norm[i][j];     P[2] = z;
		Q[0] = x+s; Q[1] = Norm[i+1][j];   Q[2] = z ;
		R[0] = x+s; R[1] = Norm[i+1][j+1]; R[2] = z+s;
		S[0] = x;   S[1] = Norm[i][j+1];   S[2] = z+s;
		
		glColor3f(.34,.49,.27);
	
	} else {
		
		P[0] = x;   P[1] = y;   P[2] = z;
		Q[0] = x+s; Q[1] = y;   Q[2] = z;
		R[0] = x+s; R[1] = y; 	R[2] = z+s;
		S[0] = x;   S[1] = y;   S[2] = z+s;
	}
	
	Normal(P,Q,S,norm);
    
    glBegin(GL_TRIANGLES);	
    
	if((P[1]<-0.01 || Q[1]<-0.01 || S[1]<-0.01)&& base) glColor3f(.88,.64,.7);
	
	if   (((P[1]>-1.5 || Q[1]>-1.5 || S[1]>-1.5 || R[1]>-1.5)&& base) || !base) {
		if(colors) glColor3f(1,0,1);
	
		glNormal3d(norm[0],norm[1],norm[2]);
	
		glTexCoord2f(t0,t1); glVertex3d(S[0],S[1],S[2]);
		glTexCoord2f(t0,t0); glVertex3d(P[0],P[1],P[2]);
		glTexCoord2f(t1,t0); glVertex3d(Q[0],Q[1],Q[2]);
	

		if(base) glColor3f(.34,.49,.27);
		if((R[1]<-0.01 || Q[1]<-0.01 || S[1]<-0.01)&& base) glColor3f(.88,.64,.7);
		if(colors) glColor3f(0,1,1);
	
		Normal(Q,R,S,norm);
		glNormal3d(norm[0],norm[1],norm[2]);

		glTexCoord2f(t1,t0); glVertex3d(Q[0],Q[1],Q[2]);
		glTexCoord2f(t1,t1); glVertex3d(R[0],R[1],R[2]);
		glTexCoord2f(t0,t1); glVertex3d(S[0],S[1],S[2]);
	
	}
	
	glEnd();

	glPopMatrix();
	

}


 //Used for the orbiting light and potentially fruit
static void ball(double x,double y,double z,double r)
{
	
   int inc=10;
   
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball with yellow specular
   float yellow[]   = {1.0,1.0,0.0,1.0};
   float Emission[] = {0.0,0.0,0.01*0,1.0};
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,0);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (int ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

void pond(double x,double y,double z) {

	glPushMatrix();
	glTranslated(x,y,z);
	
	float blue[] = {0,0,1,1};
    float Emission[]  = {0.0,0.0,0.01,1.0};
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,45);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,blue);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
	
    glColor4f(0,0,1,.75);

	
	glBegin(GL_QUADS);

	glNormal3d(0,1,0);
	glVertex3d(-125,-2,-125);
	glVertex3d(125,-2,-125);
	glVertex3d(125,-2,125);
	glVertex3d(-125,-2,125);

	glEnd();
	
	glColor3f(0,0,1);
	glDisable(GL_BLEND);
	glPopMatrix();
	


}

void cliff(double x, double y, double z) {
	
	glPushMatrix();
	
	glTranslated(x,y,z);
	
	glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE ,light?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[0]);
	
	glColor3f(0,.5,.12);
	int step=4;
	glBegin(GL_QUADS);
	
	//grass top
	glNormal3d(0,1,0);
	glTexCoord2f(0,0);glVertex3d(-60,20,10);
	glTexCoord2f(8,0);glVertex3d(-30,20,10);
	glTexCoord2f(8,8);glVertex3d(-30,0,50);
	glTexCoord2f(0,8);glVertex3d(-60,0,50);
 	
	//stone wall
	glColor3f(.5,.5,.5);
	glVertex3d(-30,0,10);
	glVertex3d(-30,0,50);
	glVertex3d(-30,20,10);
	glVertex3d(-30,0,10);
	
	glColor3f(.5,.5,.5);
	glVertex3d(-60,0,10);
	glVertex3d(-60,0,50);
	glVertex3d(-60,20,10);
	glVertex3d(-60,0,10);
	
	glEnd();
	
	int ts=1;
	int texi=0;
	 for(int z=0;z>=-20;z-=step){
		 for(int x=-124;x<35;x+=step){
			triangles(x,10,z,step,90,0,colors,3,ts,texi);
			texi = (texi+1)%ts;

		}
	}
	
	ts=2;
	texi=0;
	for(int z= 6;z>=-50;z-=step){
		 for(int x=-124;x<35;x+=step){
		 	triangles(x,20,z,step,0,0,colors,0,ts,texi);
		 	
		 }
	}
	
	glPushMatrix();
	glRotated(45,0,1,0);
	ts=1;
	texi=0;
	for(int z=0;z>=-20;z-=step){
		 for(int x=18;x<124;x+=step){
		 	triangles(x,32,z,step,90,0,colors,3,ts,texi);
			texi = (texi+1)%ts;
		}	 
	}
	
	for(int z=30;z>=-20;z-=step){
		 for(int x=18;x<124;x+=step){
		 	triangles(x,20,z,step,0,0,colors,0,ts,texi);
			texi = (texi+1)%ts;
		}	 
	}
	
	glPopMatrix();

	glPopMatrix();


}

/*
 *  Creates a Tree at (x,y,z). s scales the x and z directions while
 *  h scales the height.
 */
static void tree(double x, double y, double z, double h)
{
	//Create the leaves
	
	//I was originally using a sphere for the leaves, but I  prefer the l
	//Draw the isocahedrons with additional variables for lighting and texture
	glColor3f(0,.7,.12);
	icosahedron(x-1*h, y+3*h, z,     h,texture[0],light);
	icosahedron(x+1*h, y+3*h, z,     h,texture[0],light);
	icosahedron(x,     y+3*h, z-1*h, h,texture[0],light);
	icosahedron(x,     y+3*h, z+1*h, h,texture[0],light);
	icosahedron(x,     y+4*h, z,     h,texture[0],light);
	
	//Trunk Colors
	double r1 = 0.55;
	double g1 = 0.27;
	double b1 = 0.075;
	
	double r2 = 0.2;
	double g2 = 0.05;
	double b2 = 0.02;
	
	glPushMatrix();
	glTranslated(x,y,z);
	glScaled(h,h,h);
	
	//Enable textures for the trunk
	glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE ,light?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[1]);
    
	glColor3f(r1,g1,b1);
	glBegin(GL_QUADS);
	int d=45;
	
	//Draw the Trunk
    for (int th=0;th<=360;th+=d)
    {
    	double P[3] = {Cos(th)*.8, 0, Sin(th)*.8};
    	double Q[3] = {Cos(th)*.5, 3, Sin(th)*.5};
    	double R[3] = {Cos(th+d)*.5, 3, Sin(th+d)*.5};
    	double S[3] = {Cos(th+d)*.8,0,Sin(th+d)*.8};
    	
    	double cross[3] = {0,0,0};
    	
    	//Compute the normal
    	Normal(P,Q,R,cross);
    	
    	glNormal3f( cross[0], cross[1], cross[2]);
	    glTexCoord2f(1,1); glVertex3d(P[0],P[1],P[2]);
		glTexCoord2f(0,1); glVertex3d(Q[0],Q[1],Q[2]);   
		     
		glTexCoord2f(0,0); glVertex3d(R[0],R[1],R[2]);   
        glTexCoord2f(1,0); glVertex3d(S[0],S[1],S[2]);	
        
        //Swap Colors for definition
        if(th%2 == 0) glColor3f(r2,g2,b2);
        else glColor3f(r1,g1,b1);
        
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //Cap the bottom of the trunk
    glBegin(GL_QUAD_STRIP);
    for (int th=0;th<=360;th+=d)
    {
    	glVertex3d(0,0,0);
    	glVertex3d(Cos(th)*.8,0,Sin(th)*.8);
    
    }
    glEnd();
    glPopMatrix();
}

void perimeter() {


	glPushMatrix();
	
	// for(int x=-200; x<124;x+=24) {
// 	
// 		for(int z=100; z<200;z+=24) {
// 			tree(x,0,z,6);
// 			tree(x+12,0,z+12,6);
// 		}
// 
// 	}
// 	
// 	for(int x=100; x<200;x+=24) {
// 	
// 		for(int z=-100; z<100;z+=24) {
// 				tree(x,0,z,6);
// 			tree(x+12,0,z+12,6);
// 			
// 		}
// 	}
// 	
// 	for(int x=-200; x<=-100;x+=24) {
// 
// 	for(int z=100; z>50;z-=24) {
// 				tree(x,0,z,6);
// 			tree(x+12,0,z+12,6);
// 			
// 		}
// 	}
// 	
// 	for(int x=-200; x<=-110;x+=24) {
// 	
// 	for(int z=10; z>-40;z-=24) {
// 				tree(x,0,z,6);
// 			tree(x+12,0,z-12,6);
// 			
// 		}
// 	}
// 	
// 	for(int x=-200; x<60;x+=24) {
// 	
// 		for(int z=-120; z>-124;z-=24) {
// 			tree(x,20,z,6);
// 			tree(x+12,20,z+12,6);
// 		}
// 
// 	}
// 	
// 	for(int x=60; x<90;x+=24) {
// 	
// 		for(int z=-140; z>-160;z-=24) {
// 			tree(x,20,z,6);
// 			tree(x+12,20,z+12,6);
// 		}
// 
// 	}
	
	glPopMatrix();



}

void skybox() {

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE ,light?GL_REPLACE:GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,texture[4]);
	glBegin(GL_QUADS);
	
	glColor3f(1,1,1);
	
	glTexCoord2f(0,0); glVertex3d(-200,-200,200);
	glTexCoord2f(0,1);glVertex3d(-200,200,200);
	glTexCoord2f(1/4.0,1);glVertex3d(-200,200,-200);
	glTexCoord2f(1/4.0,0);glVertex3d(-200,-200,-200);
	
	glTexCoord2f(1/4.0,0); glVertex3d(-200,-200,-200);
	glTexCoord2f(2/4.0,0);glVertex3d(200,-200,-200);
	glTexCoord2f(2/4.0,1);glVertex3d(200,200,-200);
	glTexCoord2f(1/4.0,1);glVertex3d(-200,200,-200);
	
	glTexCoord2f(2/4.0,0); glVertex3d(200,-200,-200);
	glTexCoord2f(2/4.0,1);glVertex3d(200,200,-200);
	glTexCoord2f(3/4.0,1);glVertex3d(200,200,200);
	glTexCoord2f(3/4.0,0);glVertex3d(200,-200,200);
	
	glTexCoord2f(3/4.0,0); glVertex3d(200,-200,200);
	glTexCoord2f(3/4.0,1);glVertex3d(200,200,200);
	glTexCoord2f(4/4.0,1);glVertex3d(-200,200,200);
	glTexCoord2f(4/4.0,0);glVertex3d(-200,-200,200);
	
	glTexCoord2f(1/4.0,0.5); glVertex3d(-200,200,-200);
	glTexCoord2f(2/4.0,0.5);glVertex3d(-200,200,200);
	glTexCoord2f(3/4.0,0.5);glVertex3d(200,200,200);
	glTexCoord2f(0/4.0,0.5);glVertex3d(200,200,-200);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void lantern(double x, double y,double z) {
		
	   glShadeModel(GL_SMOOTH);
	   float Ambient[]   = {0.01*10 ,0.01*10 ,0.01*10 ,1.0};
	   float Diffuse[]   = {0.01*10 ,0.01*10 ,0.01*10 ,1.0};
	   float Specular[]  = {0.01*20,0.01*20,0.01*20,1.0};
	   float Position[] = {x,y,z,1};

	   glEnable(GL_LIGHT1);
	   //  Set ambient, diffuse, specular components and position of light 0
	   glLightfv(GL_LIGHT1,GL_AMBIENT ,Ambient);
	   glLightfv(GL_LIGHT1,GL_DIFFUSE ,Diffuse);
	   glLightfv(GL_LIGHT1,GL_SPECULAR,Specular);
	   glLightfv(GL_LIGHT1,GL_POSITION,Position);
	   
	   float yellow[]   = {1.0,1.0,0.0,1.0};
	   float Emission[] = {0.0,0.0,0.01*0,1.0};
	   glColor3f(1,1,1);
	   glMaterialf(GL_FRONT,GL_SHININESS,0);
	   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
	   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
	   
	   
	   glBegin(GL_QUADS);
	   
	   glColor3f(1,.5,0);
	   glVertex3d(x,y,z);
	   glVertex3d(x+5,y,z);
	   glVertex3d(x+5,y,z+5);
	   glVertex3d(x,y,z+5);
	   
	   glVertex3d(x,y,z);
	   glVertex3d(x+5,y,z);
	   glVertex3d(x+5,y+8,z);
	   glVertex3d(x,y+8,z);
	   
	   glVertex3d(x,y,z+5);
	   glVertex3d(x+5,y,z+5);
	   glVertex3d(x+5,y+8,z+5);
	   glVertex3d(x,y+8,z+5);
	   
	   glVertex3d(x,y,z);
	   glVertex3d(x,y+8,z);
	   glVertex3d(x,y+8,z+5);
	   glVertex3d(x,y,z+5);
	   
	   glVertex3d(x+5,y,z);
	   glVertex3d(x+5,y+8,z);
	   glVertex3d(x+5,y+8,z+5);
	   glVertex3d(x+5,y,z+5);
	   
	   glVertex3d(x,y+8,z);
	   glVertex3d(x+5,y+8,z);
	   glVertex3d(x+5,y+8,z+5);
	   glVertex3d(x,y+8,z+5);
	   glEnd();




}


void board() {

	glColorMask(0,0,0,0);
	glDepthMask(0);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS,1,1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	double clipPlane[] = {0,1,0,-2};

	pond(0,0,0);
	
	glDisable(GL_STENCIL_TEST);

		
	glDepthMask(1);
	glColorMask(1,1,1,1);
	
	// 	skybox();
	pond(0,0,0);
	mill(1,1,1,colors,zh);
	cliff(1,1,1);
	bridge(1,1,1,colors,texture[2],light);

}



void display() {

	//  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   
   if(fov) {
	   if (mode) { //Perspective view
		  Ex = -2*dim*Sin(th)*Cos(ph);
		  Ey = +2*dim        *Sin(ph);
		  Ez = +2*dim*Cos(th)*Cos(ph);
		  gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
	   //First Person
	   } else {
		  Cx = Ex + Cos(th);
		  Cz = Ez + Sin(th);
		  Cy = Ey + Cos(ph-90);
		  if(ph > 45) ph = 45;
		  if(ph < -45) ph = -45;
		  gluLookAt(Ex,Ey,Ez , Cx,Cy,Cz , 0,Cos(ph),0);
	   }
	   
      
   } else {
   	  glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   
   }
   if(!light) {
   
	   glShadeModel(GL_SMOOTH);
	   float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
	   float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
	   float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
	//     Light position

	   float Position[]  = {distance*Cos(zh)*2,distance*Sin(zh)*2,0,1.0};
	   //  Draw light position as ball (still no lighting here)
	   glColor3f(1,1,1);
	   ball(Position[0],Position[1],Position[2] , 2);
	   //  OpenGL should normalize normal vectors
	   glEnable(GL_NORMALIZE);
	   //  Enable lighting
	   glEnable(GL_LIGHTING);
	   //  Location of viewer for specular calculations
	   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,1);
	   //  glColor sets ambient and diffuse color materials
	   glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	   glEnable(GL_COLOR_MATERIAL);
	   //  Enable light 0
	   glEnable(GL_LIGHT0);
	   //  Set ambient, diffuse, specular components and position of light 0
	   glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
	   glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
	   glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
	   glLightfv(GL_LIGHT0,GL_POSITION,Position);
	   
	   //lantern(px,py,pz);
	} else {
		glDisable(GL_LIGHTING);
	}
	
   board();

   glColor3f(1,1,1);
   glWindowPos2i(5,5);
   Print("ambient: %d, diffuse: %d, specular: %d",ambient,diffuse,specular);
   Print(" Light %s",light?"Off":"On");
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  The Special keys for the program. Currently the 1st person rotation does not work as intended
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT) {
      	th += 5;
   }
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT) {
      	th -= 5;
   }
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   if (Cx>=360) Cx-=360;
   if (Cz>=360) Cz-=360;
   //  Update projection
   Project(fov,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  Executes commands on key press. 
 */
void key(unsigned char ch,int x,int y)
{
   int shift = 1;
   double scale=1.5;
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0') {
      th = ph = 0;
      Ex=-50;
	  Ey=10;
	  Ez=50;
	  Cx = -50; Cz = 50;
	  Cy = 10;
	  ambient=50;
	  diffuse=50;
	  specular=30;
	}
   //  Switch display mode
   else if (ch == 'm' || ch == 'M') {
	  mode = 1-mode;
	  th = ph = 0;
	  if(!mode) {
		 Ex=-60;
		  Ey=10;
		  Ez=50;
		  Cx = -55; Cz = 50;
		  Cy = 45;
		  fov=65;
		
	  }
   }
   //Move left no matter orientation
   else if (ch == 'a' || ch == 'A') {
        Ex += Cos(th-90)*scale;
        Ez += Sin(th-90)*scale;
        Cx += Cos(th-90)*scale;
        Cz += Sin(th-90)*scale;
   // Move right
   } else if (ch == 'd' || ch == 'D') {
        Ex += Cos(th+90)*scale;
        Ez += Sin(th+90)*scale;
        Cx += Cos(th+90)*scale;
        Cz += Sin(th+90)*scale;
    //Move forward
   } else if (ch == 'w' || ch == 'W') {
        Ex += Cos(th)*scale;
        Ez += Sin(th)*scale;
        Cx += Cos(th)*scale;
        Cz += Sin(th)*scale;
   //Move  back
   } else if (ch == 's' || ch == 'S') {
        Ex += Cos(th+180)*scale;
        Ez += Sin(th+180)*scale;
        Cx += Cos(th+180)*scale;
        Cz += Sin(th+180)*scale;
   } else if (ch=='C' || ch=='c') {
   		colors = 1-colors;
   	//Adjust ambient light
   } else if (ch == 'i' || ch == 'I') {
   		if(ch=='I') shift = -1;
   		ambient+=5*shift;
   		if(ambient>100) ambient=100;
   		if(ambient<0) ambient=0;
   		shift=1;
   		
   	//Adjust diffuse light
   } else if (ch == 'o' || ch == 'O') {
   		if(ch=='O') shift = -1;
   		diffuse+=5*shift;
   		if(diffuse>100) diffuse=100;
   		if(diffuse<0) diffuse=0;
   		shift=1;
   	//Adjust specular light
   } else if (ch == 'p' || ch == 'P') {
   		if(ch=='P') shift = -1;
   		specular+=5*shift;
   		if(specular>100) specular=100;
   		shift=1;
   } else if (ch=='l' || ch=='L') {
   		light = 1-light;
   } else if (ch=='k') {
   		stop = 1-stop;
   } else if(ch=='[') {
   		zh+=5;
   } else if(ch==']') {
   		zh-=5;
   }
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if ((ch == '=' && ch<179) || ch == '+')
      fov++;
   
   if (Cx>=360) Cx-=360;
   if (Cz>=360) Cz-=360;
   //  Reproject
   
   Project(fov,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

//Keep picture consistent when resizing
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, RES*width,RES*height);
   //  Set projection
   Project(fov,asp,dim);
}

void idle()
{
   if(stop) {
	   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
	   zh = fmod(90*t,360);
	   glutPostRedisplay();
   }
}

int main(int argc,char* argv[])
{
    //Set up random function
   srand((unsigned int)time(NULL));
   setup();
   //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitWindowSize(600,600);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   //  Create the window
   glutCreateWindow("Aidan Bolton HW3");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
   //  Tell GLUT to call "idle" when there is nothing else to do
   glutIdleFunc(idle);
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
   //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);

   texture[0] = LoadTexBMP("grass.bmp");
   texture[1] = LoadTexBMP("brick.bmp");
   texture[2] = LoadTexBMP("woodplanks.bmp");
   texture[3] = LoadTexBMP("rockwall2.bmp");
   texture[4] = LoadTexBMP("skybox.bmp");
   
//    shader = CreateShaderProg("simple.vert","simple.frag");

   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}



