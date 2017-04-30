#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <string.h>
#include <ctime>
#include <time.h>
#include <unistd.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

using namespace std ;

bool keyStates[256] = {false} ;
GLuint texture[53] ;

void resize(int, int) ;
void print_times(float, float, char *) ;
void print_9_by_15(float, float, char *) ;
void print_helvetica(float, float, char *) ;
void init(void) ;
int cardValue(int, int) ;
int get_print_value(int, int) ;
void game(void) ;
void stand() ;
void hit() ;
void keyOperations(void) ;
void keyPressed(unsigned char, int, int) ;

void resize(int height, int width) {
  const float width_height_ratio = (float) width / (float) height ;
  /* void glViewPort (GLint x, GLint y, GLsizei width, GLsizei height) ; */
  glViewport(0, 10, width, height) ;
  glMatrixMode(GL_PROJECTION) ;
  glLoadIdentity() ;
  
  /* void glFrustum (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far) ; */
  glFrustum(-width_height_ratio, width_height_ratio, -1.0, 1.0, 2.0, 90.0) ;
  glMatrixMode(GL_MODELVIEW) ;
  glLoadIdentity() ;
}

void print_times(float x, float y, char *string) {
  /* Set the position of the text in the window using the 'x' and 'y' coordinates */
  glRasterPos2f(x, y) ;
  /* Get the length of the string to display */
  int len = (int) strlen(string) ;
  /* Loop to display character by character */
  for (int i = 0; i < len; i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]) ;
}

void print_9_by_15(float x, float y, char *string) {
  glRasterPos2f(x, y) ;
  int len = (int) strlen(string) ;
  for (int i = 0; i < len; i++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]) ;
}

void print_helvetica(float x, float y, char *string) {
  glRasterPos2f(x, y) ;
  int len = (int) strlen(string) ;
  for (int i = 0; i < len; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]) ;
}

void init(void) {
  char buffer[20], rule[500] ;
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
  glClearColor(0.0274509803922f, 0.388235294118f, 0.141176470588f, 1.0f) ;
  
  sprintf(buffer, "Rules") ;
  print_times(-0.15, 0.5, buffer) ;
  
  sprintf(buffer, "Game begins in 20 seconds!") ;
  print_helvetica(-0.40, 0.4, buffer) ;
  
  sprintf(rule, "1. Draw cards to get a score as close as possible to 21, without exceeding") ;
  print_9_by_15(-1.0, 0.1, rule) ;
  sprintf(rule, "2. Hit: Press the 'h' key to take another card from the dealer") ;
  print_9_by_15(-1.0, 0.0, rule) ;
  sprintf(rule, "3. Stand: Press the 's' key to stop taking cards and move to the dealer's round") ;
  print_9_by_15(-1.0, -0.1, rule) ;
  sprintf(rule, "4. The dealer will draw more cards until his/her hand is >= 17 (could exceed 21)") ;
  print_9_by_15(-1.0, -0.2, rule) ; 
  sprintf(rule, "5. King, Queen and Jack have a score of 10") ;
  print_9_by_15(-1.0, -0.3, rule) ;
  sprintf(rule, "6. Numbered cards have the score of their value") ;
  print_9_by_15(-1.0, -0.4, rule) ;
  sprintf(rule, "7. Ace can be 1 or 11 depending on the existing score") ;
  print_9_by_15(-1.0, -0.5, rule) ;
  
  sprintf(buffer, "Enjoy!") ;
  print_times(-0.15, -0.8, buffer) ;
  
  /* Load an image file directly as a new OpenGL texture */

  /*
   * SOIL_LOAD_AUTO: Leaves the image in whatever format it was found
   * SOIL_FLAG_MIPMAPS: Generate MIPmaps for the texture
   * SOIL_FLAG_INVERT_Y: Flip the image vertically
   * SOIL_FLAG_NTSC_SAFE_RGB: Clamps RGB components to the 'safe range' of [16, 235]
   * SOIL_FLAG_COMPRESS_TO_DXT: If the card can display them, will convert RGB to DXT1, RGBA to DXT5
   */
  
  /*
   * glutSwapBuffers: 
   * Promotes the contents of the back buffer of the layer in use of the current window to become the contents of the front buffer
   * The contents of the back buffer then become undefined
   */
  
  /* Loading 'Spades' */
  
  texture[0] = SOIL_load_OGL_texture(
				     "Playing Cards/PNG-cards-1.3/ace_of_spades.png",
				     SOIL_LOAD_AUTO,
				     SOIL_CREATE_NEW_ID,
				     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				     ) ;
  texture[1] = SOIL_load_OGL_texture(
				     "Playing Cards/PNG-cards-1.3/2_of_spades.png",
				     SOIL_LOAD_AUTO,
				     SOIL_CREATE_NEW_ID,
				     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				     ) ;
  texture[2] = SOIL_load_OGL_texture(
				     "Playing Cards/PNG-cards-1.3/3_of_spades.png",
				     SOIL_LOAD_AUTO,
				     SOIL_CREATE_NEW_ID,
				     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				     ) ;
  texture[3] = SOIL_load_OGL_texture(
				     "Playing Cards/PNG-cards-1.3/4_of_spades.png",
				     SOIL_LOAD_AUTO,
				     SOIL_CREATE_NEW_ID,
				     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				     ) ;
  texture[4] = SOIL_load_OGL_texture(
				     "Playing Cards/PNG-cards-1.3/5_of_spades.png",
				     SOIL_LOAD_AUTO,
				     SOIL_CREATE_NEW_ID,
				     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				     ) ;
  texture[5] = SOIL_load_OGL_texture(
				     "Playing Cards/PNG-cards-1.3/6_of_spades.png",
				     SOIL_LOAD_AUTO,
				     SOIL_CREATE_NEW_ID,
				     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				     ) ;
  texture[6] = SOIL_load_OGL_texture(
				     "Playing Cards/PNG-cards-1.3/7_of_spades.png",
				     SOIL_LOAD_AUTO,
				     SOIL_CREATE_NEW_ID,
				     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				     ) ;
  texture[7] = SOIL_load_OGL_texture(
				     "Playing Cards/PNG-cards-1.3/8_of_spades.png",
				     SOIL_LOAD_AUTO,
				     SOIL_CREATE_NEW_ID,
				     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				     ) ;
  texture[8] = SOIL_load_OGL_texture(
				     "Playing Cards/PNG-cards-1.3/9_of_spades.png",
				     SOIL_LOAD_AUTO,
				     SOIL_CREATE_NEW_ID,
				     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				     ) ;
  texture[9] = SOIL_load_OGL_texture(
				     "Playing Cards/PNG-cards-1.3/10_of_spades.png",
				     SOIL_LOAD_AUTO,
				     SOIL_CREATE_NEW_ID,
				     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				     ) ;
  texture[10] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/king_of_spades.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[11] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/queen_of_spades.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[12] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/jack_of_spades.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  glutSwapBuffers() ;
  
  /* ________________________________________________________________________________________________ */ 
  
  usleep(20000000) ;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
  glClearColor(0.0274509803922f, 0.388235294118f, 0.141176470588f, 1.0f) ;
  
  sprintf(buffer, "Loading ...") ;
  print_times(-0.1, 0.0, buffer) ;
  
  /* Loading 'Clubs' */
  
  texture[13] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/ace_of_clubs.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[14] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/2_of_clubs.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[15] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/3_of_clubs.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[16] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/4_of_clubs.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[17] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/5_of_clubs.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[18] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/6_of_clubs.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[19] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/7_of_clubs.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[20] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/8_of_clubs.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[21] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/9_of_clubs.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[22] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/10_of_clubs.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[23] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/king_of_clubs.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[24] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/queen_of_clubs.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[25] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/jack_of_clubs.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  glutSwapBuffers() ;

  /* ________________________________________________________________________________________________ */ 
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
  glClearColor(0.0274509803922f, 0.388235294118f, 0.141176470588f, 1.0f) ;
  
  sprintf(buffer, "Loading ...") ;
  print_times(-0.1, 0.0, buffer) ;
  
  glColor3f(0.0f, 0.0f, 0.0f) ;
  sprintf(buffer, "Dealer's Cards") ;
  print_times(-0.165, 0.72, buffer) ;
  glColor3f(1.0f, 1.0f, 1.0f) ;

  /* Load 'Hearts' */
  
  texture[26] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/ace_of_hearts.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[27] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/2_of_hearts.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[28] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/3_of_hearts.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[29] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/4_of_hearts.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[30] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/5_of_hearts.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[31] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/6_of_hearts.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[32] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/7_of_hearts.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[33] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/8_of_hearts.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[34] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/9_of_hearts.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[35] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/10_of_hearts.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[36] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/king_of_hearts.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[37] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/queen_of_hearts.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[38] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/jack_of_hearts.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  glutSwapBuffers() ;
  
  /* ________________________________________________________________________________________________ */ 

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
  glClearColor(0.0274509803922f, 0.388235294118f, 0.141176470588f, 1.0f) ;
  
  sprintf(buffer, "Loading ...") ;
  print_times(-0.1, 0.0, buffer) ;
  
  glColor3f(0.0f, 0.0f, 0.0f) ;
  sprintf(buffer, "Dealer's Cards") ;
  print_times(-0.165, 0.72, buffer) ;
  glColor3f(1.0f, 1.0f, 1.0f) ;

  glColor3f(0.0f, 0.0f, 0.0f) ;
  sprintf(buffer, "Player's Cards") ;
  print_times(-0.165, -.852, buffer) ;
  glColor3f(1.0f, 1.0f, 1.0f) ;

  /* Load 'Diamonds' */
  
  texture[39] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/ace_of_diamonds.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[40] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/2_of_diamonds.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[41] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/3_of_diamonds.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[42] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/4_of_diamonds.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[43] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/5_of_diamonds.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[44] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/6_of_diamonds.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[45] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/7_of_diamonds.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[46] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/8_of_diamonds.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[47] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/9_of_diamonds.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[48] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/10_of_diamonds.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[49] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/king_of_diamonds.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[50] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/queen_of_diamonds.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[51] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/jack_of_diamonds.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  texture[52] = SOIL_load_OGL_texture(
				      "Playing Cards/PNG-cards-1.3/index.png",
				      SOIL_LOAD_AUTO,
				      SOIL_CREATE_NEW_ID,
				      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				      ) ;
  glutSwapBuffers() ;
  usleep(1000000) ;
}

void card(int r) {
  /* void glBindTexture (GLenum target, GLuint texture) ; */
  glBindTexture(GL_TEXTURE_2D, texture[r]) ;
  glBegin(GL_QUADS) ;

  /* Set the texture co-ordinates */
  glTexCoord2f(0.0f, 0.0f) ; glVertex3f(-1.0f, -1.0f,  1.0f) ;
  glTexCoord2f(1.0f, 0.0f) ; glVertex3f( 1.0f, -1.0f,  1.0f) ;
  glTexCoord2f(1.0f, 1.0f) ; glVertex3f( 1.0f,  1.0f,  1.0f) ;
  glTexCoord2f(0.0f, 1.0f) ; glVertex3f(-1.0f,  1.0f,  1.0f) ;
  
  glEnd() ;
  glTranslatef(0.5f,0.0f,0.0f) ;
  glutSwapBuffers() ;
}

int cardValue(int r, int present_score) {
  if(r % 13 == 10 || r % 13 == 11 || r % 13 == 12 || r % 13 == 0)
    if(present_score + 10 > 21)
      return 0 ;
    else
      return present_score + 10 ; 
  else if(r % 13 == 1)
    if(present_score + 11 > 21)
      if(present_score + 1 > 21)
	return 0 ;
      else
	return present_score + 1 ; 
    else
      return present_score + 11 ;
  else if(present_score + (r % 13) > 21)
    return 0 ;
  else
    return present_score + r % 13 ;     
}

int get_print_value(int r, int present_score) {
  if(r % 13 == 10 || r % 13 == 11 || r % 13 == 12 || r % 13 == 0)
    return present_score + 10; 
  else if(r % 13 == 1)
    if(present_score + 11 <= 21)
      return present_score + 1 ; 
    else
      return present_score + 11 ;
  else
    return present_score + r % 13 ;     
}

int count = 0, playerScore = 0, dealerScore = 0 ;

void game(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
  glTranslatef(0.0f, -2.0f, -9.0f) ;
  int i = 0 ;
  char buffer[20] ;
  
  glColor3f(0.0f, 0.0f, 0.0f) ;
  sprintf(buffer, "Dealer's Cards") ;
  print_times(-0.5, 4.7, buffer) ;
  glColor3f(1.0f, 1.0f, 1.0f) ;
  
  glColor3f(0.0f, 0.0f, 0.0f) ;
  sprintf(buffer, "Player's Cards") ;
  print_times(-0.5, -2.0, buffer) ;
  glColor3f(1.0f, 1.0f, 1.0f) ;
  
  usleep(500000) ;
  srand(time(NULL)) ;
  
  while(i<2) {
    int r = rand() % 52 ;
    playerScore = cardValue(r+1, playerScore) ;
    card(r) ;
    i++ ;
    usleep(500000) ;
  }

  glColor3f(0.0f, 0.0f, 0.0f);
  sprintf(buffer, "Your Points: %d", playerScore) ;
  print_times(-5.0, 0.5, buffer) ;
  glColor3f(1.0f, 1.0f, 1.0f) ;
  
  glTranslatef(-1.0f, 3.0f, 0.0f) ;
 
  int r = rand() % 52 ;
  
  dealerScore = cardValue(r+1, dealerScore) ;
  card(r) ;
  usleep(500000) ;
  card(52) ;
  
  glTranslatef(0.0f,-3.0f,0.0f) ;
}

void stand(void) {
  char buffer[20] ;
  int dcount = 0, r ;
  glTranslatef((count+1)*-0.5f, 3.0f, 0.0f) ;
  while(dealerScore < 17) {
    r = rand() % 52 ;
    card(r) ;
    if(cardValue(r+1, dealerScore)) {
      dealerScore = cardValue(r+1, dealerScore) ;
      glColor3f(0.0f, 0.0f, 0.0f) ;
      sprintf(buffer, "Dealer's Points: %d", dealerScore) ;
      print_times(-5.0-(dcount*0.5), (dcount*-0.5), buffer) ;
      glColor3f(1.0f, 1.0f, 1.0f) ;
    } else {
      cout <<"You Win!\nYour Score: " << playerScore
	   <<"\nDealer's Score: "<< get_print_value(r+1, dealerScore) << endl ;
      usleep(5000000) ;
      exit(0) ;
    }
    ++dcount ; 
    usleep(1000000) ;
  }
  
  if(playerScore > dealerScore) {
    cout << "You Win!\nYour Score: " << playerScore
	 << "\nDealer's Score: " << dealerScore << endl ;
    usleep(5000000) ;
    exit(0);
  } else if(playerScore < dealerScore) {
    cout << "You Lose!\nYour Score: " << playerScore
	 << "\nDealer's Score: " << dealerScore << endl ;
    usleep(5000000) ;
    exit(0) ;
  } else {
    cout<< "It's a Draw!\n" ;
    usleep(5000000) ;
    exit(0) ;
  } 
}
   
void hit(void) {
  char buffer[20] ;
  int r = rand() % 52 ;
  if(cardValue(r+1, playerScore)) {
    playerScore = cardValue(r+1, playerScore) ;
    card(r) ;
    glColor3f(0.0f, 0.0f, 0.0f) ;
    sprintf(buffer, "Your Points: %d", playerScore) ;
    print_times(-5.0-((count+1)*0.5), (count+1)*-0.5, buffer) ;
    glColor3f(1.0f, 1.0f, 1.0f) ;  
  } else {
    card(r) ;
    cout << "You Lose!\nYour Score: " << get_print_value(r+1, playerScore) << endl ;
    usleep(5000000) ;
    exit(0) ;
  }
  ++count ;      
}

void keyOperations(void) {
  if (keyStates['s']) {
    stand() ; 
    keyStates['s'] = false ;
  } else if (keyStates['h']) {
    hit() ; 
    keyStates['h'] = false ;
  }
} 

void keyPressed(unsigned char key, int x, int y) {
  keyStates[key] = true ;
  keyOperations() ;
}

int main(int argc, char **argv) {
  glutInit(&argc, argv) ;
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB) ;
  glutInitWindowPosition(520, 160) ;
  glutInitWindowSize(740, 700) ;
  glutCreateWindow("BlackJack v2.1") ;
  glutReshapeFunc(resize) ;
  
  init() ;
  
  glutDisplayFunc(game) ;
  glutKeyboardFunc(keyPressed) ;

  glEnable(GL_TEXTURE_2D) ;
  glShadeModel(GL_SMOOTH) ;
  glClearColor(0.0274509803922f, 0.388235294118f, 0.141176470588f, 1.0f) ;
  glClearDepth(1.0f) ;
  glEnable(GL_DEPTH_TEST) ;
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST) ;
  glutMainLoop() ;
  return 0 ;
}
