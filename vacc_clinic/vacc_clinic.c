/*
 * Name: Sinai Park (sp46)
 * Date: March 23, 2021
 * For CS232, Spring 2021
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define NUM_VIALS 30
#define SHOTS_PER_VIAL 6
#define NUM_CLIENTS (NUM_VIALS * SHOTS_PER_VIAL)
#define NUM_NURSES 10
#define NUM_STATIONS NUM_NURSES
#define NUM_REGISTRATIONS_SIMULTANEOUSLY 4

/* global variables */
int num_vials_left = NUM_VIALS;

int buffer[10];
int in = 0;
int out = 0;

//semaphores
sem_t client_sem;
sem_t vaccine_sem;
sem_t registration_sem;
sem_t empty;
sem_t full;

int get_rand_in_range(int lower, int upper)
{
    return (rand() % (upper - lower + 1)) + lower;
}

char *time_str;
char *curr_time_s()
{
    time_t t;
    time(&t);
    time_str = ctime(&t);
    // replace ending newline with end-of-string.
    time_str[strlen(time_str) - 1] = '\0';
    return time_str;
}

// lower and upper are in seconds.
void walk(int lower, int upper)
{
    // TODO: fill in code here. Use usleep() and get_rand_in_range() from above.
    usleep(get_rand_in_range(lower, upper) * 1000000);
}

// arg is the nurses station number.
void *nurse(void *arg)
{
    long int id = (long int)arg;

    fprintf(stderr, "%s: nurse %ld started\n", curr_time_s(), id);

    while (num_vials_left > 0)
    {
        walk(1, 3);
        fprintf(stderr, "%s: nurse %ld is walking to get a vial\n", curr_time_s(), id);

        if (num_vials_left == 0)
        {
            fprintf(stderr, "%s: nurse %ld finds no vaccines left. Exiting...\n", curr_time_s(), id);
            pthread_exit(NULL);
        }

        walk(1, 3); //walk back with vial
        num_vials_left--;
        fprintf(stderr, "%s: nurse %ld got a vial. # of vials left = %d\n", curr_time_s(), id, num_vials_left);

        for (int i = 0; i < 6; i++)
        {
            //indicate to the queue of clients waiting for a station assignment that you are ready for the next client.
            sem_wait(&empty); //ready

            fprintf(stderr, "%s: nurse %ld tells waiting queue she is available\n", curr_time_s(), id);
            buffer[in] = id;
            in = (in + 1) % NUM_NURSES;
            sem_post(&full);

            sem_wait(&client_sem); //wait for client to come
            fprintf(stderr, "%s: nurse %ld sees client is ready. Giving vaccine...\n", curr_time_s(), id);

            walk(5, 5); // 5 seconds wait
            fprintf(stderr, "%s: nurse %ld gave client the vaccine!\n", curr_time_s(), id);
            sem_post(&client_sem);
            sem_post(&vaccine_sem);
        }
    }

    fprintf(stderr, "%s: nurse %ld is done\n", curr_time_s(), id);
    pthread_exit(NULL);
}

void *client(void *arg)
{
    //thread creation
    long int id = (long int)arg;

    sem_wait(&registration_sem);
    fprintf(stderr, "%s: client %ld has arrived and is walking to register\n", curr_time_s(), id);
    walk(1, 2);

    //wait for an opening at registration..
    fprintf(stderr, "%s: client %ld is currently registering\n", curr_time_s(), id);

    //walk a random amount of time between 3 and 10 seconds to get to the station-assignment queue.
    walk(3, 10);
    fprintf(stderr, "%s: client %ld is done registering. Walking to next queue...\n", curr_time_s(), id);
    sem_post(&registration_sem);

    //wait for station assignment
    sem_wait(&full);
    int nurse_num = buffer[out];
    out = (out + 1) % NUM_NURSES;
    fprintf(stderr, "%s: client %ld is at station %d \n", curr_time_s(), id, nurse_num);

    //walk to nurse's station.
    walk(1, 2);

    //wait for the nurse to complete the vaccination
    sem_post(&client_sem);
    sem_wait(&vaccine_sem);
    fprintf(stderr, "%s: client %ld got the vaccine! \n", curr_time_s(), id);

    //leave the clinic
    fprintf(stderr, "%s: client %ld leaves the clinic!\n", curr_time_s(), id);
    sem_post(&empty);
    pthread_exit(NULL);
}

//main function to create semaphores necessary for simulation
int main()
{
    srand(time(0));

    //create semaphores
    // source code from https://shivammitra.com/c/producer-consumer-problem-in-c/#
    sem_init(&vaccine_sem, 0, 0);
    sem_init(&client_sem, 0, 0);
    sem_init(&registration_sem, 0, 4);
    sem_init(&empty, 0, NUM_NURSES);
    sem_init(&full, 0, 0);

    //create two threads;
    pthread_t client_t[NUM_CLIENTS];
    pthread_t nurse_t[NUM_NURSES];

    //create nurse threads
    for (long int i = 0; i < NUM_NURSES; i++)
        pthread_create(&nurse_t[i], NULL, nurse, (void *)i);
    //create client threads (0 to 1 s random delay)
    for (long int i = 0; i < NUM_CLIENTS; i++) {
        pthread_create(&client_t[i], NULL, client, (void *)i);
        walk(0, 1);
    }
    pthread_exit(0);
}