#ifndef ANIMATION_THREAD_H
#define ANIMATION_THREAD_H

#include <GL/freeglut.h>

#include "main.h"
#include "draw.h"
#include "user_interaction.h"
#include "terminalinfo.h"
#include "trigonometry.h"

bool animation_running = false;
std::string bmp_loc;
/**
 * Main animation loop.
 * Takes care of drawing the agents in their corrective location.
 */
void main_loop_function()
{
  if (!animation_running) {
    terminalinfo::info_msg("Animation started.");
    animation_running = true;
  }

  // Add depth (used internally to block obstructed objects)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  // Get current window size w.r.t. beginning
  xrat = (float)param->window_width() / (float)glutGet(GLUT_WINDOW_WIDTH);
  yrat = (float)param->window_height() / (float)glutGet(GLUT_WINDOW_HEIGHT);

  zoom_scale = -(float)10 / (-(float)10 + (float)zoom);
  glTranslatef(center_x, center_y, -10 + zoom);

  // Draw fixed one time objects
  static draw drawer; // Drawer object
  bmp_loc = "conf/environments/image_testing/gas_simulations/iteration_"+std::to_string((int)(floor(simtime_seconds)))+".bmp";
  drawer.bmp_bg(bmp_loc.c_str());
  drawer.data(); // Put data in corner
  drawer.axes(); // Put x and y global axes
  drawer.axis_label(); // Axis label
  drawer.source(); //draw source position as red dot
  environment.animate(); // Animate the environment walls
  
  // Draw all robots
  uint r = s.size();
  if (r > 0) {
    for (uint16_t ID = 0; ID < r; ID++) {
      // Input: ID, p_x global, p_y global, orientation global
      drawer.agent(ID, s[ID]->state.at(0), s[ID]->state.at(1), s[ID]->orientation);
      // Input: ID, p_x global, p_y global, v_x global, v_y global
      drawer.velocity_arrow(ID,  s[ID]->state.at(0), s[ID]->state.at(1), s[ID]->state.at(2), s[ID]->state.at(3));
      drawer.segment(s[ID]->state[1],s[ID]->state[0],s[ID]->laser_pnts[0][0],s[ID]->laser_pnts[0][1]);
      terminalinfo::debug_msg("1:" + std::to_string(s[ID]->state[0]));
      terminalinfo::debug_msg("2:" + std::to_string(s[ID]->state[1]));
      terminalinfo::debug_msg("3:" + std::to_string(s[ID]->laser_pnts[0][0]));
      terminalinfo::debug_msg("4:" + std::to_string(s[ID]->laser_pnts[0][1]));
    }
  }

  // Swap buffers (color buffers, makes previous render visible)
  glutSwapBuffers();

  user_interaction(); // Activate interactive functions (mouse + keyboard), important: use this before draw functions!
  if (!program_running) {std::terminate();}
}

/**
 * Initialze OpenGL perspective matrix
 *
 * @param width Width of the animation window
 * @param height Height of the animation window
 */
void GL_Setup(int width, int height)
{
  glViewport(0, 100, width, height);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(45, (float)width / height, .1, 100);
  glMatrixMode(GL_MODELVIEW);
}

/**
 * Thread function that initiates the animation
 */
void main_animation_thread()
{
  // Initialize all variables
  center_x = 0;
  center_y = 0;
  sx = 0;
  sy = 0;
  zoom = param->zoom();
  zoom_scale = 0;
  pointer_x = 0;
  pointer_y = 0;
  paused = false;
  xrat = 1.0;
  yrat = 1.0;

  // Set up simulation window
  int argc = 1;
  char *argv[1] = {(char *)"  "};
  glutInit(&argc, argv);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(param->window_width(), param->window_height());
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutCreateWindow("Swarmulator");
  glutIdleFunc(main_loop_function);
  GL_Setup(param->window_width(), param->window_height()); // Set up window parameters
  glutMainLoop(); // Initiate main drawing loop
}

#endif /*ANIMATION_THREAD_H*/
