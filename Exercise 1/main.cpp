#include <iostream>
#include <time.h>
#include <pthread.h>

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <omp.h>

using namespace std;

#define NUM_THREADS omp_get_max_threads() // To get the maximum thread the computer can provide

// Call of function used in the progra : utils.cpp
double generate_random_double();
bool in_circle(double x, double y);
void *increment(void *threadarg);
void writeTitle(string title, string infos="");
 
// Global variable accessible from all the program
double circle=0;
pthread_mutex_t lock;

// Creat the structure with the argument needed by the thread
struct thread_data{
    int thead_id;
    int start;
    int stop;
   
};


// Function to be used by the thread
void *increment(void *threadarg)
{
    // Create new struct and assign the value of the argument
    struct thread_data *my_data;
    my_data=(struct thread_data *) threadarg;
    // Now we can access to the value of our variable by using pointer
    for(int i=my_data->start; i<my_data->stop; i++)
    {
        double x=generate_random_double();
        double y=generate_random_double();
        if(in_circle(x, y)){
            pthread_mutex_lock(&lock);
                circle++;
            pthread_mutex_unlock(&lock);
        }
    }

    pthread_mutex_lock(&lock);
        cout <<" Thread id : " << my_data->thead_id << " Circle account : " << circle <<"\t Starting point : "<< my_data->start <<"\t Ending point : "<< my_data->stop <<endl;
    pthread_mutex_unlock(&lock);
   
    pthread_exit(NULL);
}


 
int main() {
    writeTitle("Welcome to the program : π ESTIMATION", "by Group1");
    //
    pthread_t threads[NUM_THREADS]; //The 5 threads identifiers
    struct thread_data td[NUM_THREADS]; //Table of 5 thread data

    pthread_attr_t attr;
    void* status;
    //init the attr
    pthread_attr_init(&attr);


    int rc; //the ouput of thread creation. Use to check if everything is ok
    cout.precision(40);
    int N = 1000000000;
    srand(time(NULL));
  

    int start=0;
    int step= N/NUM_THREADS;
    int stop= step;
    for(int i=0; i<NUM_THREADS; i++)
    {
        //Assigining the variable
        td[i].start=start;
        td[i].stop=stop;
        td[i].thead_id=i;
        // intptr_t a= (intptr_t) i;
        // (void *) a;
        rc=pthread_create(&threads[i],  &attr, increment, (void *)  &td[i]);
        if(rc){
            cout <<"Error:unable to create thread, " << rc <<endl;
            exit(-1);
        }
        start=stop;
        stop=stop + N/NUM_THREADS;
    }


    for(int i=0; i<NUM_THREADS; i++)
    {
        // Her we use the value of a thread not the address
        // The function will wait the specific thread to finish:
        //The function will overide the &status for each thread
        rc=pthread_join(threads[i], &status);
        // rc -> 0 success
        if(rc){
            cout <<"Error:Cannot join the thread, " << rc << endl;
            exit(-1);
        }

    }
    
    double pi = 4.0 * (double) circle / N ;
    int n=omp_get_max_threads();
    cout << "Num  of points : " << N << "\t PI = " << pi << endl;
    cout << "In circle : " << circle << endl;
    cout << "Maximum thread : " << n <<endl;
    
    return 0;
}

// we want 20 decimals of pi.