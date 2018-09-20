#include "max7219.h"
#include "mbed.h"
#include "MQTTEthernet.h"
#include "MQTTClient.h"
#define ECHO_SERVER_PORT   7
max7219 m; 
char buff[100];
int i=11.2;
char result[10];
int arrivedcount = 0;
 
void messageArrived(MQTT::MessageData& md)
{
    MQTT::Message &message = md.message;
    
    sprintf(result, "%.*s", message.payloadlen,(char*)message.payload);
//    strcpy(s,(char*)message.payload);
    printf("%s \n",result);
//    memset(result,'\0',sizeof(result));
    m.send(result);
    printf("Message arrived: qos %d, retained %d, dup %d, packetid %d\n", message.qos, message.retained, message.dup, message.id);
    printf("Payload %.*s\n", message.payloadlen, (char*)message.payload);
    ++arrivedcount;
}

void baud(int baudrate) 
{
    Serial s(USBTX, USBRX);
    s.baud(baudrate);
}

//Defining hex code for "HELLO"
char Hello[]={0xa2,0xa2,0xa2,0xbe,0xa2,0xa2,0xa2,0xa2,
           0xdf,0x40,0x40,0x5f,0x5f,0x40,0x40,0x5f,
            0xf7,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
            0x79,0x84,0x84,0x84,0x84,0x84,0x84,0x78};      
int main() 
{
    baud(115200);
    printf("Wait a second...\r\n");
    char* topic = "sristy";
    MQTTEthernet ipstack = MQTTEthernet();
    
    MQTT::Client<MQTTEthernet, Countdown> client = MQTT::Client<MQTTEthernet, Countdown>(ipstack);
    
    char* hostname = "172.16.73.4";
    int port = 1883;
    
    int rc = ipstack.connect(hostname, port);
   // if (rc != 0)
//        printf("rc from TCP connect is %d\n", rc);  
    
    printf("Topic: %s\r\n",topic);
    
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;       
    data.MQTTVersion = 3;
    data.clientID.cstring = "parents";

    if ((rc = client.connect(data)) != 0)
        printf("rc from MQTT connect is %d\n", rc);
    m.send("DEFT");
    while(1)
    {
        if ((rc = client.subscribe(topic, MQTT::QOS1, messageArrived)) != 0)
            printf("rc from MQTT subscribe is %d\n", rc); 
        client.yield(60000);
        m.init();
    }

       
}