#include <ros.h>
#include <std_msgs/String.h>

#define InputAA 7
#define InputAB 8
#define InputBA 9
#define InputBB 10
#define PWMOutputMotorA 5
#define PWMOutputMotorB 6

ros::NodeHandle nh;
std_msgs::String str_msg;

char* cmd; 

void messageCb(const std_msgs::String& command){
  sprintf(cmd, "%s", command.data);
}

ros::Subscriber<std_msgs::String> sub("command", &messageCb );

void leftTurn() {
  digitalWrite(InputAA, HIGH);
  digitalWrite(InputBA, HIGH);
  digitalWrite(InputBB, LOW);
  digitalWrite(InputAB, LOW);
}


void rightTurn() {
  digitalWrite(InputAA, LOW);
  digitalWrite(InputBA, LOW);
  digitalWrite(InputBB, HIGH);
  digitalWrite(InputAB, HIGH);
}


void forward() {
  digitalWrite(InputAA, HIGH);
  digitalWrite(InputBA, LOW);
  digitalWrite(InputBB, HIGH);
  digitalWrite(InputAB, LOW);
}


void backward() {
  digitalWrite(InputAA, LOW);
  digitalWrite(InputBA, HIGH);
  digitalWrite(InputBB, LOW);
  digitalWrite(InputAB, HIGH);
}

void freeRun() {
  digitalWrite(InputAA, LOW);
  digitalWrite(InputBA, LOW);
  digitalWrite(InputBB, LOW);
  digitalWrite(InputAB, LOW);
}

void brake() {
  digitalWrite(InputAA, HIGH);
  digitalWrite(InputBA, HIGH);
  digitalWrite(InputBB, HIGH);
  digitalWrite(InputAB, HIGH);
}

void setup(){
  pinMode(PWMOutputMotorA,OUTPUT);
  pinMode(PWMOutputMotorB,OUTPUT);
  pinMode(InputAA,OUTPUT);
  pinMode(InputAB,OUTPUT);
  pinMode(InputBA,OUTPUT);
  pinMode(InputBB,OUTPUT);

  Serial.begin(9600);

  nh.initNode();
  nh.subscribe(sub);
  
}

void loop(){
  if (cmd[0]=='f')
    forward();
  else if (cmd[0]=='b')
    backward();
  else if (cmd[0]=='l')
    leftTurn();
  else if (cmd[0]=='r')
    rightTurn();
  else if (cmd[0]=='s')
    brake();
  else freeRun();

}
