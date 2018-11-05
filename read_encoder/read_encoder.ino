unsigned char encPin[] = {14, 15, 16, 17, 18, 19, 3, 4, 5, 6};
int encResolution = 1024;
int zero = 100;//679
int data = 0;
int lastdata = 0;
int cyclic_data=0;
float degree;
float ref = 2.;
float err=0;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 10; i++) {
    pinMode(encPin[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  data = getEncData(); //encoder data tik
  cyclic_data = cyclicMap(data, zero, encResolution);
  degree = myMap(cyclic_data, encResolution);
  err = degree - ref;
  if(data!=lastdata){
    Serial.print(data);
    Serial.print("\t");
    Serial.print(cyclic_data);
    Serial.print("\t");
    Serial.print(degree);  
    Serial.print("\t");
    Serial.println(err);  
    lastdata = data;
  }
  
}

float myMap(long sensorRead, int res) {
  return (float(sensorRead) / float(res)) * 360 - 180.0;
}

int cyclicMap(int currentPos, int zeroPos, int res) {
  int cyclicVal = 0 ;
  if (currentPos < zeroPos) {
    cyclicVal = (currentPos % zeroPos)+ (res - zeroPos);
  }
  else cyclicVal = currentPos - zeroPos;
  return cyclicVal;
}

int greyCodeData() {
  int greyCode = 0;
  int status = !digitalRead(encPin[9]);
  //Serial.print(status);
  greyCode =   status * pow(2, 9);
  status = !digitalRead(encPin[8]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 8);
  status = !digitalRead(encPin[7]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 7);
  status = !digitalRead(encPin[6]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 6);
  status = !digitalRead(encPin[5]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 5);
  status = !digitalRead(encPin[4]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 4);
  status = !digitalRead(encPin[3]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 3);
  status = !digitalRead(encPin[2]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 2);
  status = !digitalRead(encPin[1]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 1);
  status = !digitalRead(encPin[0]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 0);
  //Serial.println( greyCode );
  //Serial.println();
  return greyCode;
}

int getEncData() {
  long num = greyCodeData();
  //Serial.print("Grey Code = "); Serial.println(greyCode);
  num = num ^ (num >> 16);
  num = num ^ (num >> 8);
  num = num ^ (num >> 4);
  num = num ^ (num >> 2);
  num = num ^ (num >> 1);
  //Serial.println(num);
  return int(num);
}
