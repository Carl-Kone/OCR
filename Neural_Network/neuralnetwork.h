#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <err.h>

typedef struct neuron_t
{
	float actv;
	float *out_weights;
	float bias;
	float z;

	float dactv;
	float *dw;
	float dbias;
	float dz;

} neuron;

neuron create_neuron(size_t num_out_weights);

size_t init(void);
size_t dinit(void);

size_t create_network(void);
size_t initialize_weights(void);
void feed_input(size_t i);
void train_neural_net(void);
void forward_propagation(void);
void forward_propagation_train(void);
void compute_cost(size_t i);
void b_propagation(size_t p);
void update_weights(void);
void get_inputs(void);
void get_xor_outputs(void);
void test_neuralnetwork(void);

size_t initialize_dummy_weights(void);

typedef struct layer_t
{
	size_t num_neu;
	struct neuron_t *neu; 
} layer;

layer create_layer(size_t num_neurons);

#endif
