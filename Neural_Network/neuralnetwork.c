#include "neuralnetwork.h"

/*
 * Function: create_neuron
 * ----------------------------
 *   creates a neuron
 *
 *    arg1: num of weights going out of neuron
 *    .....
 *
 *   returns: created neuron
 */
neuron create_neuron(int num_out_weights)
{
	neuron neu;

	neu.actv = 0.0;
	neu.out_weights = (float*) malloc(num_out_weights * sizeof(float));
	neu.bias=0.0;
	neu.z = 0.0;

	neu.dactv = 0.0;
	neu.dw = (float*) malloc(num_out_weights * sizeof(float));
	neu.dbias = 0.0;
	neu.dz = 0.0;

	return neu;
}

/*
 * Function: create_layer
 * ----------------------------
 *   creates a layer
 *
 *    arg1: num of neuron
 *    .....
 *
 *   returns: created layer
 */
layer create_layer(int number_of_neurons)
{
	layer lay;
	lay.num_neu = -1;
	lay.neu = (struct neuron_t *) malloc(number_of_neurons * sizeof(struct neuron_t));
	return lay;
}
