#include "WGP.h"


void wheel(double x, double y, double z,int colors,int zh) {
	glPushMatrix();
	glTranslated(x,y,z);
	glRotated(-zh,1,0,0);
	glScaled(10,10,10);
	
	glColor3f(.69,.51,.55);
	int d = 15;
	glBegin(GL_QUADS);
	
	
    for (int th=0;th<=360;th+=d) {
    	

    	
		double P[3] = {0,Cos(th)  , Sin(th)};
    	double Q[3] = {0,Cos(th)*.8  , Sin(th)*.8};
    	double R[3] = {0,Cos(th+d)*.8, Sin(th+d)*.8};
    	double S[3] = {0,Cos(th+d), Sin(th+d)};
    	
    	double norm[3] = {0,0,0};
    	
    	Normal(P,Q,R,norm);
    	//Left Side
    	glNormal3f( norm[0], norm[1], norm[2]);
    	
		glVertex3d(P[0],P[1],P[2]);
		glVertex3d(Q[0],Q[1],Q[2]);    
		glVertex3d(R[0],R[1],R[2]);   
		glVertex3d(S[0],S[1],S[2]);	
		
		//Right Side
		glNormal3f( norm[0]*(-1), norm[1]*(-1), norm[2]*(-1));
		glVertex3d(P[0]+1,P[1],P[2]);
		glVertex3d(Q[0]+1,Q[1],Q[2]);   
		glVertex3d(R[0]+1,R[1],R[2]);   
		glVertex3d(S[0]+1,S[1],S[2]);	
		
		//Center
		glNormal3f(1,1,0);
		glVertex3d(P[0]+1.1,P[1]*.2,P[2]*.2);
		glVertex3d(S[0]+1.1,S[1]*.2,S[2]*.2);
		glVertex3d(1.1,0,0);
		glVertex3d(P[0]+1.1,P[1]*.2,P[2]*.2);
		
		//Buckets
		glColor3f(.88,.64,.7);
		if(colors) glColor3f(0,1,0);
		glNormal3f( norm[0], norm[1], norm[2]);
    	
    	glVertex3d(S[0],S[1],S[2]);
		glVertex3d(Q[0],Q[1],Q[2]);    
		glVertex3d(Q[0]+1,Q[1],Q[2]);   
		glVertex3d(S[0]+1,S[1],S[2]);	
		
		//back
		glColor3f(.69,.51,.55);
		double temp[3] = {Q[0],Q[1],Q[2]};
		temp[0]+=1;
		Normal(R,Q,temp,norm);
// 		glNormal3f( norm[0]*(-1), norm[1]*(-1), norm[2]*(-1));
    	glNormal3f( norm[0], norm[1], norm[2]);
				
		glVertex3d(Q[0],Q[1],Q[2]);  
    	glVertex3d(Q[0]+1,Q[1],Q[2]);   
		glVertex3d(R[0]+1,R[1],R[2]);
		glVertex3d(R[0],R[1],R[2]); 
		
		//Center Pole
		
		glNormal3f( norm[0], norm[1], norm[2]);
		glVertex3d(Q[0]-1,Q[1]*.25,Q[2]*.25);  
    	glVertex3d(Q[0]+1.1,Q[1]*.25,Q[2]*.25);   
		glVertex3d(R[0]+1.1,R[1]*.25,R[2]*.25);
		glVertex3d(R[0]-1,R[1]*.25,R[2]*.25); 
		
		// glVertex3d(Q[0]-1,Q[1]*.75,Q[2]*.75);  
//     	glVertex3d(Q[0]+1.1,Q[1]*.75,Q[2]*.75);   
// 		glVertex3d(R[0]+1.1,R[1]*.75,R[2]*.75);
// 		glVertex3d(R[0]-1,R[1]*.75,R[2]*.75); 
		
    }
    

    d=30;
    int shift=1;
    for(int i=1;i>=0;i--) {
    
		for (int th=0;th<=360;th+=d) {
		
			double P[3] = {i,Cos(th-4)*.8  , Sin(th-4)*.8};
			double Q[3] = {i,Cos(th+4)*.8, Sin(th+4)*.8};
			double R[3] = {i+.1*shift,Cos(th+5)*.2, Sin(th+5)*.2};
			double S[3] = {i+.1*shift,Cos(th-5)*.2, Sin(th-5)*.2};
		
			double norm[3] = {0,0,0};
			Normal(P,Q,R,norm);
			glNormal3f( norm[0], norm[1], norm[2]);
		
			if(colors) glColor3f(0,1,0);
			glVertex3d(P[0],P[1],P[2]);
			glVertex3d(Q[0],Q[1],Q[2]);    
			glVertex3d(R[0],R[1],R[2]);   
			glVertex3d(S[0],S[1],S[2]);	
		
			glNormal3f( norm[0]*(-1), norm[1]*(-1), norm[2]*(-1));
			glVertex3d(P[0]-.1*shift,P[1],P[2]);
			glVertex3d(Q[0]-.1*shift,Q[1],Q[2]);    
			glVertex3d(R[0]-.1*shift,R[1],R[2]);   
			glVertex3d(S[0]-.1*shift,S[1],S[2]);
		
			double temp[3] = {Q[0],Q[1],Q[2]};
			temp[0]-=8;
			Normal(R,Q,temp,norm);
		
			if(colors) glColor3f(1,0,0);
			glNormal3f( norm[0]*(-1), norm[1]*(-1), norm[2]*(-1));
			glVertex3d(Q[0],Q[1],Q[2]);
			glVertex3d(Q[0]-.1*shift,Q[1],Q[2]);    
			glVertex3d(R[0]-.1*shift,R[1],R[2]);   
			glVertex3d(R[0],R[1],R[2]);
		
			temp[0]=P[0]; temp[1]=P[1]; temp[2]=temp[2];
			temp[0]-=8;
			Normal(P,S,temp,norm);
		
			if(colors) glColor3f(0,0,1);
			glNormal3f( norm[0]*(-1), norm[1]*(-1), norm[2]*(-1));
			glVertex3d(P[0],P[1],P[2]);
			glVertex3d(S[0],S[1],S[2]);
			glVertex3d(S[0]-.1*shift,S[1],S[2]); 
			glVertex3d(P[0]-.1*shift,P[1],P[2]);  
		
		}
		shift=-1;
	}
	glEnd();
	
	glPopMatrix();

}


void mill(double x, double y, double z, int colors, int zh) {
	
	glPushMatrix();
	
	glTranslated(x,y,z);
	
	glColor3f(.85,.50,.30);
	glNormal3d(0,1,0);
	
	float red[] = {.85,.17,.26,1};
    float Emission[]  = {0.0,0.0,0.01,1.0};
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,5);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,red);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
	int step=2;
	
	//Front
	int texi=0;
	int ts = 4;
	for(int x=0;x<20;x+=step) {
		for(int z=-16;z<2;z+=step) {

			if (!(x>=10 && x<=14 && z>=-12))
				if (!(x>=2 && x<=6 && z<=-8 && z>=-12))
					triangles(x,10,z,step,90,90,colors,1,ts,texi);
					texi = (texi+1)%ts;
		}
	}
	//Back
	texi=0;
	for(int x=0;x<20;x+=step) {
		for(int z=-16;z<8;z+=step) {
			triangles(x,-18,z,step,90,90,colors,1,ts,texi);
			texi = (texi+1)%ts;
		}
	}
	
	//Left side
	texi=0;
	for(int x=-10;x<18;x+=step) {
		for(int z=-16;z<4;z+=step) {

			if (!(x>=-6 && x<=-2 && z<=-8 && z>=-12))
				if (!(x>=8 && x<=12 && z<=-8 && z>=-12))
					triangles(x,20,z,step,90,0,colors,1,ts,texi);
					texi = (texi+1)%ts;
		}
	}
	
	//Right
	texi=0;
	for(int x=-10;x<18;x+=step) {
		for(int z=-16;z<4;z+=step) {

			triangles(x,0,z,step,90,0,colors,1,ts,texi);
			texi = (texi+1)%ts;
		}
	}
	
	//glColor3f(.5,.51,.5);
	//Upper Level
	texi=0;
	ts=4;
	for(int x=0;x<20;x+=step) {
		for(int z=-32;z<-16;z+=step) {
		
					triangles(x,0,z,step,90,90,colors,2,ts,texi);
					texi = (texi+1)%ts;
		}
	}
	
	//back
	texi=0;
	for(int x=0;x<20;x+=step) {
		for(int z=-32;z<-16;z+=step) {

					triangles(x,-18,z,step,90,90,colors,2,ts,texi);
					texi = (texi+1)%ts;
		}
	}
	
	//LeftSide
	texi=0;
	for(int x=0;x<18;x+=step) {
		for(int z=-32;z<-16;z+=step) {

			if (!(x>=8 && x<=12 && z<=-22 && z>=-26))
				triangles(x,20,z,step,90,0,colors,2,ts,texi);
				texi = (texi+1)%ts;
		}
	}
	texi=0;
	for(int x=0;x<18;x+=step) {
		for(int z=-32;z<-16;z+=step) {
		
				triangles(x,0,z,step,90,0,colors,2,ts,texi);
				texi = (texi+1)%ts;
		}
	}
	
	//Roof Triangles
	glBegin(GL_TRIANGLES);
	
	glNormal3f(0,0,-1);
	glVertex3d(0,32,0);
	glVertex3d(0,40,10);
	glVertex3d(0,32,20);
	
	glNormal3f(0,0,-1);
	glVertex3d(18,32,0);
	glVertex3d(18,40,10);
	glVertex3d(18,32,20);
	
	glNormal3f(0,0,-1);
	glVertex3d(-10,16,0);
	glVertex3d(-10,24,10);
	glVertex3d(-10,16,20);
	
	glEnd();
	
	//Roof rectangles
	glColor3f(.5,.5,.5);
	glBegin(GL_QUADS);
	
	glNormal3f(1,1,0);
	glVertex3d(-2,40,10);
	glVertex3d(22,40,10);
	glVertex3d(22,28,-5);
	glVertex3d(-2,28,-5);

	glNormal3f(-1,1,0);
	glVertex3d(-2,40,10);
	glVertex3d(22,40,10);
	glVertex3d(22,28,25);
	glVertex3d(-2,28,25);
	
	glNormal3f(-1,1,0);
	glVertex3d(-12,24,10);
	glVertex3d(0,24,10);
	glVertex3d(0,12,25);
	glVertex3d(-12,12,25);
	
	glNormal3f(1,1,0);
	glVertex3d(-12,24,10);
	glVertex3d(0,24,10);
	glVertex3d(0,16,0);
	glVertex3d(-12,16,0);

	glEnd();
	
	glPopMatrix();
	
	wheel(31,6,-28,colors,zh);
	
}
