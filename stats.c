#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

void usage();
int is_valid_int(char *s);
int *generate_population(int size, int lower, int upper);
void get_stats(int *a, int size, int *min, int *max, double *mean, double *stddev);


void usage(){
	printf("usage: stats samples population lowerbound upperbound\n\tsamples: number of samples\n\tpopulation: number of random values to generate in each sample\n\tlowerbound: bottom of random number range\n\tupperbound: top of random number range\n");
	exit(0);
}

int *generate_population(int size, int lower, int upper){
	srand(time(NULL));
	int randomnum = rand(); 
	int *population = (int*)malloc(size *sizeof(int));
	int counter =0;
	for (int i = 0; i < size; ++i){
		if (randomnum > lower && upper > randomnum && counter < size){
			population[i] = randomnum;
			if (counter == size){
				break;
			}
			++counter;
		       	
		}
		else
			--counter;
	}
	return population;
}

void get_stats(int *a, int size, int *min, int *max, double *mean, double *stddev){
	
	double sum = 0;
	int calcmin = a[0];
	int calcmax = a[0];
	for (int i = 0; i < size; ++i)
	{
		sum += a[i];
		for (int i = 1; i < size; ++i){
			if (a[i] < calcmin){
				calcmin = a[i];
			}
			else if (a[i] > calcmax){
				calcmax = a[i];
			}
			else{
				continue;
			}
		}
	}	
	double meancalculation = sum/size;
	mean = &meancalculation;
	double calcmean = *mean;
	double stdsum;
	for (int i = 0; i < size; ++i){
		stdsum += (pow((double)a[i] - calcmean,2)/(double)size);
	}
	stddev = &stdsum; 
	mean = &meancalculation;
	min = &calcmin;
	max = &calcmax;
}



int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i){	
	if (argc < 5 || is_valid_int(argv[i]) == 0 || argc > 5 || atoi(argv[2]) < 1 || atoi(argv[3]) < 1){
		if (argc < 4 || is_valid_int(argv[i]) == 0 || argc > 4){
			usage();
			break;
		}
		else if (atoi(argv[2]) < 1){
			printf("samples must be a positive integer\n");
			usage();
			break;
		}
		else if (atoi(argv[3]) < 1){
			printf("population must be a positive integer\n");
			usage();
			break;
		}
		else if (is_valid_int(argv[i]) == 0){
			printf("all arguments must be integers");
			usage();
			break;
		}

	}
	else{
		int samples = atoi(argv[1]);
		for (int i = 0; i < samples; ++i){
			int popsize = atoi(argv[2]);
			int lowerbound = atoi(argv[3]);
			int higherbound = atoi(argv[4]);
			int *generated = generate_population(popsize, lowerbound, higherbound);
			int *min;
			int *max; 
			double *mean;
			double *stddev;
			get_stats(generated, popsize, min, max, mean, stddev);
			printf("Sample %i: min = %p, max = %p, mean = %p, stddev = %p\n", i, min, max, mean, stddev);
		}
	}
    } 
}

int is_valid_int(char *s)
{
    if (s == NULL)
    {
        return -1;    
    }

    if (*s == '-')
    {
        ++s;
    }
    while (*s != '\0')
    {
        if (!isdigit(*s))
        {
            return 0;
        }
        ++s;
    }
    return 1;
}

