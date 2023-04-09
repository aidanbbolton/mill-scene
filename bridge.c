#include "WGP.h"

void bridge(double x, double y, double z, int colors,unsigned int tex,int light) {

	x=-45; y=-12; z=30;
	float red[] = {1,0,0,1};
	float brown[] = {1,.54,.5,1};
    float Emission[]  = {0.0,0.0,0.01,1.0};
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,5);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,red);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
    
    if(!colors) {
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE ,light?GL_REPLACE:GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D,tex);
	} else {
		glDisable(GL_TEXTURE_2D);
	}
	
	for(int i=0;i<=20;i+=20) {
		glPushMatrix();
		glTranslated(x-i,y,z);
		glScaled(20,20,20);
		int d=10;
		glColor3f(1,0,0);
		glBegin(GL_QUADS);
		int shift = 1;
		for (int th=-50;th<50;th+=d) {
	
			double P[3] = {0,Cos(th)  , Sin(th)};
			double Q[3] = {0,Cos(th)*.85  , Sin(th)*.85};
			double R[3] = {0,Cos(th+d)*.85, Sin(th+d)*.85};
			double S[3] = {0,Cos(th+d), Sin(th+d)};
			double norm[3] = {0,0,0};
		
			if(colors) glColor3f(0,1,0);
			Normal(P,Q,R,norm);
			glNormal3f( norm[0], norm[1], norm[2]);    	
		
			/*
				Bridge Side Base
			*/
			//Right Side
			glVertex3d(P[0],P[1],P[2]);
			glVertex3d(Q[0],Q[1],Q[2]);    
			glVertex3d(R[0],R[1],R[2]);   
			glVertex3d(S[0],S[1],S[2]);
		
			//Left Side
			glNormal3f( norm[0]*(-1), norm[1]*(-1), norm[2]*(-1));
			glVertex3d(P[0]-.15,P[1],P[2]);
			glVertex3d(Q[0]-.15,Q[1],Q[2]);    
			glVertex3d(R[0]-.15,R[1],R[2]);   
			glVertex3d(S[0]-.15,S[1],S[2]);
		
			//Top
			if(colors) glColor3f(1,0,0);
			glNormal3f( 0, 1, 0);
			glVertex3d(P[0],P[1],P[2]);
			glVertex3d(P[0]-.15,P[1],P[2]);    
			glVertex3d(S[0]-.15,S[1],S[2]);   
			glVertex3d(S[0],S[1],S[2]);
		
			//Bottom
			if(colors) glColor3f(0,0,1);
			glNormal3f( 0, -1, 0);
			glVertex3d(Q[0],Q[1],Q[2]);
			glVertex3d(Q[0]-.15,Q[1],Q[2]);    
			glVertex3d(R[0]-.15,R[1],R[2]);   
			glVertex3d(R[0],R[1],R[2]);
		
			/*
				Bridge Rails
			*/
		
			double scale=0.025;
			for(int ph=0;ph<360;ph+=d) {
		
				double temp[] = {P[0]-.075+Cos(ph)*scale,P[1]-.075+Sin(ph)*scale+.2,P[2]};
				double temp1[]= {P[0]-.075+Cos(ph+d)*scale,P[1]-.075+Sin(ph+d)*scale+.2,P[2]};
				double temp2[]= {S[0]-.075+Cos(ph+d)*scale,S[1]-.075+Sin(ph+d)*scale+.2,S[2]};
				Normal(temp,temp1,temp2,norm);
				glNormal3f( norm[0], norm[1], norm[2]);    	
			
				glVertex3d(P[0]-.075+Cos(ph)*scale,P[1]-.075+Sin(ph)*scale+.2,P[2]);
				glVertex3d(P[0]-.075+Cos(ph+d)*scale,P[1]-.075+Sin(ph+d)*scale+.2,P[2]);    
				glVertex3d(S[0]-.075+Cos(ph+d)*scale,S[1]-.075+Sin(ph+d)*scale+.2,S[2]);   
				glVertex3d(S[0]-.075+Cos(ph)*scale,S[1]-.075+Sin(ph)*scale+.2,S[2]);
		
			}
			
			if(!i) {
			
				glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,brown);
				glColor3f(brown[0],brown[1],brown[2]);
				if(colors) glColor3f(0,1,1*shift);
				glNormal3f( 0, 1, 0);		
				glTexCoord2f(1,0); glVertex3d(P[0],P[1]-.1,P[2]);
				glTexCoord2f(0,0); glVertex3d(P[0]-1,P[1]-.1,P[2]);    
				glTexCoord2f(0,1); glVertex3d(S[0]-1,S[1]-.1,S[2]);   
				glTexCoord2f(1,1); glVertex3d(S[0],S[1]-.1,S[2]);
				shift*=-1;
				glColor3f(1,0,0);
				
			}
		}

		double zoffset=1;
	
		for(int i=0;i<2;i++) {
	
			glNormal3f(0,0,-1);
			if(colors) glColor3f(0,1,0);
			glVertex3d(-0.15,.5,.6*zoffset);
			glVertex3d(0,.5,.6*zoffset);
			glVertex3d(0,1,.6*zoffset);
			glVertex3d(-0.15,1,.6*zoffset);
	
			glNormal3f(0,0,1);
			glVertex3d(-0.15,.5,.78*zoffset);
			glVertex3d(0,.5,.78*zoffset);
			glVertex3d(0,1,.78*zoffset);
			glVertex3d(-0.15,1,.78*zoffset);
			
			glNormal3f(0,1,0);
			glVertex3d(-0.15,1,.6*zoffset);
			glVertex3d(0,1,.6*zoffset);
			glVertex3d(0,1,.78*zoffset);
			glVertex3d(-0.15,1,.78*zoffset);
				

			if(colors) glColor3f(0,0,1);
			glNormal3f(-1,0,0);
			glNormal3f(0,0,1);
			glVertex3d(-0.15,.5,.6*zoffset);
			glVertex3d(-0.15,.5,.78*zoffset);
			glVertex3d(-0.15,1,.78*zoffset);
			glVertex3d(-0.15,1,.6*zoffset);	
	
			if(colors) glColor3f(1,0,0);
			glNormal3f(1,0,0);
			glVertex3d(0,.5,.6*zoffset);
			glVertex3d(0,.5,.78*zoffset);
			glVertex3d(0,1,.78*zoffset);
			glVertex3d(0,1,.6*zoffset);		
		
		
			zoffset=-1;
		}
	glEnd();
	glPopMatrix();
	}

}