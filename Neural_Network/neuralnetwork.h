#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

neuron create_neuron(int num_out_weights);


typedef struct layer_t
{
	int num_neu;
	struct neuron_t *neu; 
} layer;

layer create_layer(int num_neurons);

#endif
