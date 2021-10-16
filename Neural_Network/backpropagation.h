#ifndef BACKPROP_H
#define BACKPROP_H

#include "neuralnetwork.h"

int init(void);

//Defining everything here
int create_architecture(void);
int initialize_weights(void);
void feed_input(int i);
void train_neural_net(void);
void forward_prop(void);
void forward_prop_train(void);
void compute_cost(int i);
void back_prop(int p);
void update_weights(void);
void get_inputs(void);
void get_desired_outputs(void);
void test_nn(void);

int initialize_dummy_weights(void);


#endif
