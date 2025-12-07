#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Customer
{
    int arrivalTime;
    struct Customer *next;
} Customer;
typedef struct Queue
{
    Customer *front;
    Customer *rear;
    int length;
} Queue;
void enqueue(Queue *q, int arrival)
{
    Customer *temp = malloc(sizeof(Customer));
    temp->arrivalTime = arrival;
    temp->next = NULL;
    if (q->rear == NULL)
    {
        q->front = q->rear = temp;
    }
    else
    {
        q->rear->next = temp;
        q->rear = temp;
    }
    q->length++;
}
int dequeue(Queue *q)
{
    if (q->front == NULL)
        return -1;
    Customer *temp = q->front;
    int arrival = temp->arrivalTime;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    q->length--;
    return arrival;
}
int main()
{
    srand(time(NULL));
    Queue q = {NULL, NULL, 0};
    int simTime = 100;
    int serviceEndTime = 0; // When current service ends
    int totalCustomers = 0;
    int servedCustomers = 0;
    int totalWaitTime = 0;
    int maxQueueLength = 0;
    for (int t = 0; t < simTime; t++)
    {
        // Random arrival: 30% chance a new customer arrives
        if (rand() % 10 < 3)
        {
            enqueue(&q, t);
            totalCustomers++;
            if (q.length > maxQueueLength)
                maxQueueLength = q.length;
        }
        // If server is free
        if (t >= serviceEndTime && q.front != NULL)
        {
            int arrival = dequeue(&q);
            int wait = t - arrival;
            totalWaitTime += wait;
            servedCustomers++;
            // service time random between 2 and 5
            int serviceTime = 2 + rand() % 4;
            serviceEndTime = t + serviceTime;
        }
    }
    printf("----- Simulation Result -----\n");
    printf("Total Customers Arrived: %d\n", totalCustomers);
    printf("Customers Served: %d\n", servedCustomers);
    printf("Maximum Queue Length: %d\n", maxQueueLength);
    printf("Average Waiting Time: %.2f\n",
           servedCustomers > 0 ? (float)totalWaitTime / servedCustomers : 0);
    return 0;
}
