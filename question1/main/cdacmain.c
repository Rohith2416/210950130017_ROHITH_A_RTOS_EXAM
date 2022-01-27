#include<stdio.h>
#include <freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/queue.h>

xQueueHandle xQueue;
TaskHandle_t xHandle_1;
TaskHandle_t xHandle_2;

void task1(void *pv)
{
	printf("Task 1 with periodicity 1000ms\n");
	vTaskDelay(1000/portTICK_PERIOD_MS);
}

void task2(void *pv)
{
	printf("Task 1 with periodicity 2000ms\n");
	vTaskDelay(2000/portTICK_PERIOD_MS);
}

void task3(void *pv)
{
	printf("Task 1 with periodicity 5000ms\n");
	vTaskDelay(5000/portTICK_PERIOD_MS);
}

void sensortask_1(void *pv)
{
    int sensor_data=0;
    while(1)
    {
        sensor_data++;
        printf("SENSOR TASK  RUNNING:%d\n",sensor_data);
        xQueueSend(queue,&sensor_data,portMAX_DELAY);
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}
void Alarmtask_1(void *pv)
{
    int rece_data=0; 
    while(1)
    {
        //printf("ALARM TASK  RUNNING: %d\n",rece_data);
        xQueueReceive(queue,&rece_data,portMAX_DELAY);
        printf("RECEIVED DATA %d\n",rece_data);
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}
void app_main()
{
    queue=xQueueCreate(4,sizeof(int));
    BaseType_t result;
     result=xTaskCreate(task1,"task1",2048,NULL,9,NULL);
      result=xTaskCreate(task2,"task2",2048,NULL,9,NULL);
       result=xTaskCreate(task3,"task3",2048,NULL,9,NULL);
    result=xTaskCreate(sensortask_1,"sensortask_1",2048,NULL,8,&xHandle_1);

    if(result==pdPASS)
    {
        printf("sensortask created\n");
    }
    result=xTaskCreate(Alarmtask_1,"Alarmtask_1",2048,NULL,9,&xHandle_2);

    if(result==pdPASS)
    {
        printf("Alarmtask created\n");
    }
}
