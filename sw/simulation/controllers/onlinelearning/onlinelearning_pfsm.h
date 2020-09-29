#ifndef ONLINELEARNING_PFSM_H
#define ONLINELEARNING_PFSM_H

#include <stdio.h>
#include <iostream>
#include "controller.h"
#include "pagerank_estimator.h"
#include "randomgenerator.h"
#include "trigonometry.h"
#include "template_calculator.h"
#include <armadillo>
#define COMMAND_LOCAL 1  // Local frame

class onlinelearning_pfsm: public Controller
{
  Template_Calculator t;
  uint moving_timer;
  int selected_action;
  uint timelim;
  float vmean;
  arma::mat policy;
  uint st; // current state
  float vx_ref, vy_ref;
  arma::mat pol;
  pagerank_estimator p;

public:

  onlinelearning_pfsm();
  static double fitness(const arma::vec &inputs, arma::vec *grad_out, void *opt_data);
  void action_motion(const int &selected_action, float r, float t, float &v_x, float &v_y);
  void state_action_lookup(const int ID, uint state_index);
  virtual void get_velocity_command(const uint16_t ID, float &v_x, float &v_y);
  virtual void animation(const uint16_t ID);
};

#endif /*ONLINELEARNING_PFSM_H*/