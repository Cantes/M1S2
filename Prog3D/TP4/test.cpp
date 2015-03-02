#include <GL/glut.h>
#include <stdlib.h>

GLfloat angle = 0.0 ;

void display(void) {
 glClear(GL_COLOR_BUFFER_BIT) ;
 glLoadIdentity() ;
 glRotatef(angle,0,0,1) ;
 glRectf(-0.5,-0.5,0.5,0.5) ;
 glutSwapBuffers() ;
}

void keyboard(unsigned char key, int x, int y) {
 switch (key) {
 case ' ':
 angle ++ ;

 
 
 glMatrixMode(GL_PROJECTION) ;
 glLoadIdentity() ;
 glOrtho(-5.0, 5, -5.0, 5, -5.0, 5) ;
 glMatrixMode(GL_MODELVIEW) ;
 glLoadIdentity() ;
 
  glutPostRedisplay() ;
 break ;
 case 27 /* Esc */:
 exit(1) ;
 }
}


int main(int argc, char **argv) {
 glutInit(&argc, argv) ;
 glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE) ;
 glutCreateWindow(argv[0]) ;
 glutDisplayFunc(display) ;
 glutKeyboardFunc(keyboard) ;
 glutMainLoop() ;
 return 0 ;
}
