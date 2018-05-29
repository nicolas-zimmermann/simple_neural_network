#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct neurone {
    double z;
    double b;
    double * weights;
};

void printy(struct neurone * output, int nOutput) {
    int i;
    printf("y(x) : ");
    for(i = 0; i< nOutput; i++) {
	printf("%.3lf ", output[i].z);
    }
    printf("\n");
}

void calcul(struct neurone * layer0, struct neurone * layer1, int nNeuroneLayer0, int nNeuroneLayer1) {
    int i, j;
    for(i = 0; i < nNeuroneLayer1; i++) {
	for(j = 0; j < nNeuroneLayer0; j++) {
	    layer1[i].z += layer0[j].z * layer0[j].weights[i];
	    
	}
	if(i%100 == 0) {
	    printf("post sig neurone[%d].z : %lf\n", i, layer1[i].z);
	}
	layer1[i].z = 1/(1+(exp(-(layer1[i].z - layer1[i].b))));
	if(i%100 == 0) {
	    printf("neurone[%d].z : %lf\n", i, layer1[i].z);
	}
    }
}


int fill_input(struct neurone * inputlayer, int nInput, char * datafile, char * labelfile, long image) {
    int i;
    double z;
    unsigned char c, lab;
    
    FILE * data = fopen(datafile, "r");
    if(data == NULL) {
	fprintf(stderr,"erreur d'ouverture du fichier data\n");
	exit(1);
    }
    FILE * label = fopen(labelfile, "r");
    if(label == NULL) {
	fprintf(stderr,"erreur d'ouverture du fichier label\n");
	exit(1);
    }
    
    fseek(data, 16+(nInput*image), SEEK_SET);    
    for(i = 0; i < nInput; i++) {
	fread(&c, 1, 1, data);
	z = (double )c;
	if(z > 0) {printf(" %.1lf", z);}
	inputlayer[i].z = z;
    }

    fseek(label, 8 + image, SEEK_SET);
    fread(&lab, 1, 1, label);
    printf("\n");
    i = (int)lab;
    printf("label : %d\n", i);
    fclose(data);
    fclose(label);
    return i;
}

void bigfree(struct neurone ** layer, int nInput, int nHiddenLayer, int nNeuroneHidden) {
    int i,j;
    for(i = 0; i < nInput; i++) {
	free(layer[0][i].weights);
    }
    free(layer[0]);

    for(i = 1; i <= nHiddenLayer; i++) {
	for(j = 0; j < nNeuroneHidden; j++) {
	    free(layer[i][j].weights);
	}
	free(layer[i]);    
    }
    
    free(layer[nHiddenLayer + 1]);
}


void calculus(struct neurone ** layer, int nInput, int nOutput, int nNeuroneHidden, int nHiddenLayer) {
    int i;
    for(i = 1; i <= nHiddenLayer + 1; i++) {
	if(i == 1) {
	    calcul(layer[i - 1], layer[i], nInput, nNeuroneHidden);
	}
	else if(i == nHiddenLayer + 1) {
	    calcul(layer[i - 1], layer[i], nNeuroneHidden, nOutput);
	}
	else {
	    calcul(layer[i-1], layer[i], nNeuroneHidden, nNeuroneHidden);	    
	}
    }
}

void initialisation(struct neurone ** layer, int nInput, int nOutput, int nHiddenLayer, int nNeuroneHidden) {
    int i, j, k;
    layer[0] = malloc(nInput * sizeof(struct neurone));
    for(i = 0; i < nInput; i++) {
	layer[0][i].weights = malloc(nNeuroneHidden * sizeof(double));
	for(k = 0; k < nNeuroneHidden; k++) {
	    layer[0][i].weights[k] = 0.5;
	}
	layer[0][i].z = 0;
	layer[0][i].b = 1;
    }   
    for(i = 1; i <= nHiddenLayer; i++) {
    	layer[i] = malloc(nNeuroneHidden * sizeof(struct neurone));
	if(i < nHiddenLayer) {
	    for(j = 0; j < nNeuroneHidden; j++) {
		layer[i][j].weights = malloc(nNeuroneHidden * sizeof(double));
		for(k = 0; k < nNeuroneHidden; k++) {
		    layer[i][j].weights[k] = 0.5;
		}
		layer[i][j].z = 0;
		layer[i][j].b = 1;
	    }
	}
	else {
	    for(j = 0; j < nNeuroneHidden; j++) {
		layer[i][j].weights = malloc(nOutput * sizeof(double));
		for(k = 0; k < nOutput; k++) {
		    layer[i][j].weights[k] = 0.5;
		}
		layer[i][j].z = 0;
		layer[i][j].b = 1;
	    }
	}	    
    }    
    layer[nHiddenLayer + 1] = malloc(nOutput * sizeof(struct neurone));
}

int main (int argc, char ** argv) {
    if(argc != 3) {
	fprintf(stderr,"erreur : pas assez d'argument : %s data labels\n", argv[0]);
	exit(1);
    }
    srand(time(NULL));
    int nInput = 728 ,nOutput = 10, nHiddenLayer = 3, nNeuroneHidden = 800;
    int label;
    long image;
    /*
    printf("how many neurons in the input layer : ");
    scanf("%d", &nInput);
    printf("how many neurons in the output layer : ");
    scanf("%d", &nOutput);
    printf("how many neurons in the hidden layers :");
    scanf("%d", &nNeuroneHidden);
    printf("how many hidden layer : ");
    scanf("%d", &nHiddenLayer);
    */
    printf("image : ");
    scanf("%li", &image);
    
    struct neurone * layer[nHiddenLayer + 2];
    
    //structure initialisation
    initialisation(layer, nInput, nOutput, nHiddenLayer, nNeuroneHidden);
    
  
    //loading input
    label = fill_input(layer[0], nInput, argv[1], argv[2], image);

    
    //missing : actual deep-learning / weight and biais adaptation 
    // 


    //calculus
    calculus(layer, nInput, nOutput, nNeuroneHidden, nHiddenLayer);
    

    //vecteur y(x)
    printy(layer[nHiddenLayer+1], nOutput);


    //freeing space
    bigfree(layer, nInput, nHiddenLayer, nNeuroneHidden);

    return 0;
}
