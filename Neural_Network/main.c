#include "neuralnetwork.h"


layer *lay = NULL;
size_t num_layers;
size_t *num_neurons;
float learning_rate;
float *cost;
float full_cost;
float **input;
float **desired_outputs;
size_t num_training_ex;
size_t n=1;

int main(void)
{
    size_t i;

    num_layers = 3;

    num_neurons = (size_t*) malloc(num_layers * sizeof(size_t));
    memset(num_neurons,0,num_layers *sizeof(size_t));

    // Get number of neurons per layer
    num_neurons[0] = 2;
    num_neurons[1] = 2;
    num_neurons[2] = 1;

    printf("\n");

    // Initialize the neural network module
    if(init()!= 0)
    {
        printf("Error in Initialization...\n");
        exit(0);
    }

    learning_rate = 0.30;

    num_training_ex = 4;
    printf("\n");

    input = (float**) malloc(num_training_ex * sizeof(float*));
    for(i=0;i<num_training_ex;i++)
    {
        input[i] = (float*)malloc(num_neurons[0] * sizeof(float));
    }

    desired_outputs = (float**) malloc(num_training_ex* sizeof(float*));
    for(i=0;i<num_training_ex;i++)
    {
        desired_outputs[i] = (float*)malloc(num_neurons[num_layers-1] * sizeof(float));
    }

    cost = (float *) malloc(num_neurons[num_layers-1] * sizeof(float));
    memset(cost,0,num_neurons[num_layers-1]*sizeof(float));

    // Get Training Examples
    get_inputs();

    // Get Output Labels
    get_xor_outputs();

    train_neural_net();
    test_neuralnetwork();

    return 0;
}


size_t init()
{
    if(create_network() != 0) 
    {
        return 1;
    }
    printf("Neural Network Created\n");
    printf("\n");
    return 0;
}

/*
 * Function: get_inputs
 * ----------------------------
 *   Different inputs, pre created
 *   In our case, we only need it to learn XOR 
 *   (Can also learn other logic gates)
 *
 *    arg1: -
 *    .....
 *
 *   returns: -
 */
void  get_inputs()
{
    input[0][0] = 0;
    input[0][1] = 0;
    input[1][0] = 0;
    input[1][1] = 1;
    input[2][0] = 1;
    input[2][1] = 0;
    input[3][0] = 1;
    input[3][1] = 1;
}

/*
 * Function: get_xor_outputs()
 * ----------------------------
 *   Ask desired outputs to user
 *
 *    arg1: stdin (desired outputs)
 *    .....
 *
 *   returns: -
 */
void get_xor_outputs()
{
    printf("Enter the output corresponding to the size_tput: %s \n","0 0");
    scanf("%f",&desired_outputs[0][0]);
    printf("\n");
    printf("Enter the output corresponding to the size_tput: %s \n","0 1");
    scanf("%f",&desired_outputs[1][0]);
    printf("\n");
    printf("Enter the output corresponding to the size_tput: %s \n","1 0");
    scanf("%f",&desired_outputs[2][0]);
    printf("\n");
    printf("Enter the output corresponding to the size_tput: %s \n","1 1");
    scanf("%f",&desired_outputs[3][0]);
    printf("\n");
}

/*
 * Function: feed_input
 * ----------------------------
 *   Sends input values to each neuron of the 1st layer
 *
 *    arg1: number of inputs // neurons
 *    .....
 *
 *   returns: WHAT IT RETURNs
 */
void feed_input(size_t i)
{
    size_t j;

    for(j=0;j<num_neurons[0];j++)
    {
        lay[0].neu[j].actv = input[i][j];
    }
}

/*
 * Function: create_network
 * ----------------------------
 *   creates the network
 *   allocates memory
 *   calls create_layer and create_neuron
 *
 *    arg1: -
 *    .....
 *
 *   returns: 0
 */
size_t create_network()
{
    printf("---Creating Neural Network---\n");
    printf("\n");

    size_t i=0,j=0;
    lay = (layer*) malloc(num_layers * sizeof(layer));

    for(i=0;i<num_layers;i++)
    {
        lay[i] = create_layer(num_neurons[i]);
        lay[i].num_neu = num_neurons[i];

        for(j=0;j<num_neurons[i];j++)
        {
            if(i < (num_layers-1)) 
            {
                lay[i].neu[j] = create_neuron(num_neurons[i+1]);
            }
 
        }

        
    }

    printf(" - Layers created\n");
    printf("\n");

    // Initialize the weights
    if(initialize_weights() != 0)
    {
        printf("Error\n");
        return 1;
    }

    return 0;
}

/*
 * Function: initialize_weights
 * ----------------------------
 *   For each neuron of each layer, exept the output layer
 *   randomly generates weights
 *
 *    arg1: -
 *    .....
 *
 *   returns: 0
 */
/*
void load_weights()
{
    FILE* fptr = fopen("saved_weights", "r");
    char line[6];

    while (fgets(line, sizeof(line), fptr)) 
    {
        printf("%s", line); 
    }
    fclose(fptr);
}
*/
size_t initialize_weights(void)
{
    size_t i,j,k;

    printf(" - Assigning weights\n");
    printf("\n");

    for(i=0;i<num_layers-1;i++)
    {
        
        for(j=0;j<num_neurons[i];j++)
        {
            for(k=0;k<num_neurons[i+1];k++)
            {
                // Initialize Output Weights for each neuron
                lay[i].neu[j].out_weights[k] = ((double)rand())/((double)RAND_MAX);
                lay[i].neu[j].dw[k] = 0.0;

                printf("  ->  Weight : %f\n", lay[i].neu[j].out_weights[k]);
            }

            if(i>0) 
            {
                lay[i].neu[j].bias = ((double)rand())/((double)RAND_MAX);
            }
        }
    }   
    printf("\n");

    printf("-----------------------------\n");
    printf("\n");
    
    for (j=0; j<num_neurons[num_layers-1]; j++)
    {
        lay[num_layers-1].neu[j].bias = ((double)rand())/((double)RAND_MAX);
    }

    return 0;
}

/*
 * Function: train_neural_net
 * ----------------------------
 *   Trains the neural network, calling different functions
 *
 *    arg1: -
 *    .....
 *
 *   returns: -
 */
void train_neural_net(void)
{
    size_t i;
    size_t it=0;

    // Gradient Descent
    for(it=0;it<20000;it++)
    {
        for(i=0;i<num_training_ex;i++)
        {
            feed_input(i);
            forward_propagation_train();
            compute_cost(i);
            b_propagation(i);
            update_weights();
        }
    }


    printf("Training Done!\n");
    printf("\n");
}


/*
 * Function: update_weights
 * ----------------------------
 *   Updates weight with the learning rate (Tested with a learning rate of 3 and it didn't work)
 *   Current learning rate : 0.3
 *
 *    arg1: -
 *    .....
 *
 *   returns: -
 */
void update_weights(void)
{
    size_t i,j,k;

    for(i=0;i<num_layers-1;i++)
    {
        for(j=0;j<num_neurons[i];j++)
        {
            for(k=0;k<num_neurons[i+1];k++)
            {
                // Update Weights
                lay[i].neu[j].out_weights[k] = (lay[i].neu[j].out_weights[k]) - (learning_rate * lay[i].neu[j].dw[k]);
                printf("Updated weight => %f\n", lay[i].neu[j].out_weights[k]);
                printf("\n");
            }
            
            // Update Bias
            lay[i].neu[j].bias = lay[i].neu[j].bias - (learning_rate * lay[i].neu[j].dbias);
        }
    }   
}

/*
 * Function: forward_propagation_train
 * ----------------------------
 *    This version is for the training
 *    Calls for activations function
 *    Computes the output of neuron, either 1 or 0
 *    Depends if the number is largely positive or negative
 *
 *    arg1: -
 *    .....
 *
 *   returns: -
 */
void forward_propagation_train(void)
{
    size_t i,j,k;

    for(i=1;i<num_layers;i++)
    {   
        for(j=0;j<num_neurons[i];j++)
        {
            lay[i].neu[j].z = lay[i].neu[j].bias;

            for(k=0;k<num_neurons[i-1];k++)
            {
                lay[i].neu[j].z  = lay[i].neu[j].z + ((lay[i-1].neu[k].out_weights[j])* (lay[i-1].neu[k].actv));
            }

            // Relu Activation Function for Hidden Layers
            if(i < num_layers-1)
            {
                if((lay[i].neu[j].z) < 0)
                {
                    lay[i].neu[j].actv = 0;
                }

                else
                {
                    lay[i].neu[j].actv = lay[i].neu[j].z;
                }
            }
            
            // Sigmoid Activation function for Output Layer
            else
            {
                lay[i].neu[j].actv = 1/(1+exp(-lay[i].neu[j].z));
            }
        }
    }
}

/*
 * Function: forward_propagation
 * ----------------------------
 *   same as above
 *
 *    arg1: -
 *    .....
 *
 *   returns: -
 */
void forward_propagation(void)
{
    size_t i,j,k;

    for(i=1;i<num_layers;i++)
    {   
        for(j=0;j<num_neurons[i];j++)
        {
            lay[i].neu[j].z = lay[i].neu[j].bias;

            for(k=0;k<num_neurons[i-1];k++)
            {
                lay[i].neu[j].z  = lay[i].neu[j].z + ((lay[i-1].neu[k].out_weights[j])* (lay[i-1].neu[k].actv));
            }

            // Relu Activation Function for Hidden Layers
            if(i < num_layers-1)
            {
                if((lay[i].neu[j].z) < 0)
                {
                    lay[i].neu[j].actv = 0;
                }

                else
                {
                    lay[i].neu[j].actv = lay[i].neu[j].z;
                }
            }
            
            // Sigmoid Activation function for Output Layer
            else
            {
                lay[i].neu[j].actv = 1/(1+exp(-lay[i].neu[j].z));
                printf("Output: %zu\n", (size_t)round(lay[i].neu[j].actv));
                printf("\n");
            }
        }
    }

    //save weights
    FILE *fptr = fopen("saved_weights", "w");
    if(fptr == NULL)
    {
        errx(1, "ERROR: The file was not created");
    }
    for(i=0;i<num_layers-1;i++)
    {
        for(j=0;j<num_neurons[i];j++)
        {
            for(k=0;k<num_neurons[i+1];k++)
            {
                fprintf(fptr,"%f\n", lay[i].neu[j].out_weights[k]);
            }
        }
    }
    fclose(fptr);
}

/*
 * Function: compute_cost
 * ----------------------------
 *   computes the cost,
 *   quantifier to find weights and biases
 *
 *    arg1: num outputs
 *    .....
 *
 *   returns: -
 */
void compute_cost(size_t i)
{
    size_t j;
    float tmpcost=0;
    float tcost=0;

    for(j=0;j<num_neurons[num_layers-1];j++)
    {
        tmpcost = desired_outputs[i][j] - lay[num_layers-1].neu[j].actv;
        cost[j] = (tmpcost * tmpcost)/2;
        tcost = tcost + cost[j];
    }   

    full_cost = (full_cost + tcost)/n;
    n++;
}

/*
 * Function: b_propagation
 * ----------------------------
 *   Fast way of computing the cost function
 *
 *    arg1: num of outputs
 *    .....
 *
 *   returns: -
 */
void b_propagation(size_t p)
{
    size_t i,j,k;

    // Output Layer
    for(j=0;j<num_neurons[num_layers-1];j++)
    {           
        lay[num_layers-1].neu[j].dz = (lay[num_layers-1].neu[j].actv - desired_outputs[p][j]) * (lay[num_layers-1].neu[j].actv) * (1- lay[num_layers-1].neu[j].actv);

        for(k=0;k<num_neurons[num_layers-2];k++)
        {   
            lay[num_layers-2].neu[k].dw[j] = (lay[num_layers-1].neu[j].dz * lay[num_layers-2].neu[k].actv);
            lay[num_layers-2].neu[k].dactv = lay[num_layers-2].neu[k].out_weights[j] * lay[num_layers-1].neu[j].dz;
        }
            
        lay[num_layers-1].neu[j].dbias = lay[num_layers-1].neu[j].dz;
    }

    // Hidden Layers
    for(i=num_layers-2;i>0;i--)
    {
        for(j=0;j<num_neurons[i];j++)
        {
            if(lay[i].neu[j].z >= 0)
            {
                lay[i].neu[j].dz = lay[i].neu[j].dactv;
            }
            else
            {
                lay[i].neu[j].dz = 0;
            }

            for(k=0;k<num_neurons[i-1];k++)
            {
                lay[i-1].neu[k].dw[j] = lay[i].neu[j].dz * lay[i-1].neu[k].actv;
                if(i>1)
                {
                    lay[i-1].neu[k].dactv = lay[i-1].neu[k].out_weights[j] * lay[i].neu[j].dz;
                }
            }

            lay[i].neu[j].dbias = lay[i].neu[j].dz;
        }
    }
}

/*
 * Function: test_neuralnetwork
 * ----------------------------
 *   Called after the training,
 *   Test values of outputs according to inputs
 *
 *    arg1: -
 *    .....
 *
 *   returns: -
 */
void test_neuralnetwork(void) 
{
    size_t i;
    for(size_t j = 0; j < 6; j++)
    {
        printf("Input:\n");

        for(i=0;i<num_neurons[0];i++)
        {
            scanf("%f",&lay[0].neu[i].actv);
        }
        forward_propagation();
    }
    printf("Weights successfully saved\n");
    //load_weights();

    //free mem
    free(num_neurons);
    free(input);
    free(desired_outputs);
    free(cost);
    free(lay);
}
