
#include "WGP.h"

typedef struct {float x,y,z;} vtx;
typedef struct {int A,B,C;} tri;
const int N=20;

//  Triangle index list
const tri idx[] =
   {
      { 2, 1, 0}, { 3, 2, 0}, { 4, 3, 0}, { 5, 4, 0}, { 1, 5, 0},
      {11, 6, 7}, {11, 7, 8}, {11, 8, 9}, {11, 9,10}, {11,10, 6},
      { 1, 2, 6}, { 2, 3, 7}, { 3, 4, 8}, { 4, 5, 9}, { 5, 1,10},
      { 2, 7, 6}, { 3, 8, 7}, { 4, 9, 8}, { 5,10, 9}, { 1, 6,10}
   };
//  Vertex coordinates
const vtx xyz[] =
   {
      { 0.000, 0.000, 1.000}, { 0.894, 0.000, 0.447}, { 0.276, 0.851, 0.447},
      {-0.724, 0.526, 0.447}, {-0.724,-0.526, 0.447}, { 0.276,-0.851, 0.447},
      { 0.724, 0.526,-0.447}, {-0.276, 0.851,-0.447}, {-0.894, 0.000,-0.447},
      {-0.276,-0.851,-0.447}, { 0.724,-0.526,-0.447}, { 0.000, 0.000,-1.000}
   };


static void triangle(vtx A,vtx B,vtx C)
{
   //  Planar vector 0
   float dx0 = A.x-B.x;
   float dy0 = A.y-B.y;
   float dz0 = A.z-B.z;
   //  Planar vector 1
   float dx1 = C.x-A.x;
   float dy1 = C.y-A.y;
   float dz1 = C.z-A.z;
   //  Normal
   float Nx = dy0*dz1 - dy1*dz0;
   float Ny = dz0*dx1 - dz1*dx0;
   float Nz = dx0*dy1 - dx1*dy0;
   //  Draw triangle
   glNormal3f(Nx,Ny,Nz);
   glBegin(GL_TRIANGLES);
   glTexCoord2f(0.0  ,0.0);
   glVertex3f(A.x,A.y,A.z);
   glTexCoord2f(1  ,0.0);
   glVertex3f(B.x,B.y,B.z);
   glTexCoord2f(1/2  ,1);
   glVertex3f(C.x,C.y,C.z);
   glEnd();
}

/*
 *  Draw icosahedron
 *     at (x,y,z)
 *     size  s
 *     rotated th about the x axis
 */
void icosahedron(float x,float y,float z,float s, unsigned int t,int light)
{

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE ,light?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,t);

   //  Draw icosahedron
   glPushMatrix();
   glTranslatef(x,y,z);
   glScalef(s,s,s);
   
   
   
   glRotatef(0,0,1,0);
   glRotatef(-90,1,0,0);
   for (int i=0;i<N;i++)
      triangle(xyz[idx[i].A],xyz[idx[i].B],xyz[idx[i].C]);
	
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
   
}


// // Vertex with the addition of Normals
// void Vertex(double th,double ph)
// {
//    double x = Sin(th)*Cos(ph);
//    double y = Cos(th)*Cos(ph);
//    double z =         Sin(ph);
// 
//    glNormal3d(x,y,z);
//    glVertex3d(x,y,z);
// }

/*
 *  Draw a sphere 
 *     at (x,y,z)
 *     radius (r)
 */

// static void sphere(double x,double y,double z,double s)
// {
//    const int d=15;
// 
//    //  Save transformation
//    glPushMatrix();
//    //  Offset and scale
//    glTranslated(x,y,z);
//    glScaled(s,s,s);
//    double r = .38;
//    double g = .54;
//    double b = .24;
// 
//    glColor3f(r,g,b);
//    
//    // glEnable(GL_TEXTURE_2D);
// //    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE ,GL_REPLACE);
// //    glBindTexture(GL_TEXTURE_2D,texture[0]);
//    double rep=10;
//    //  Latitude bands
//    for (int ph=-90;ph<90;ph+=d)
//    {
//       glBegin(GL_QUAD_STRIP);
// 
//       for (int th=0;th<=360;th+=d)
//       {
//       	 glTexCoord2f(Cos(th*rep),Sin(ph*rep));
//          Vertex(th,ph);
//          glTexCoord2f(Cos(th*rep),Sin(ph+d*rep));
//          Vertex(th,ph+d);
//       }
//       glEnd();
//    }
//    glDisable(GL_TEXTURE_2D);
//    //  Undo transformations
//    glPopMatrix();
// }