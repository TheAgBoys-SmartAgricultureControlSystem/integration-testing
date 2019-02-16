int nodeid = 0;
int nodestatus = 0;
int rssi = 0;
float lat = 0;
float lng = 0;
int soil = 0;

void node_write(int nodeid, int rssi, float lat, float lng, int soil){
  //Serial.write("start_packet");
  Serial.write("NodeId:");
  Serial.print(nodeid, HEX);
  Serial.write("#");
  Serial.write("SoilMoisture:");
  Serial.print(soil);
  Serial.write("#");
  Serial.write("Latitude:");
  Serial.print(lat);
  Serial.write("#");
  Serial.write("Longitude:");
  Serial.print(lng);
  Serial.write("#");
  Serial.write("RSSI:");
  Serial.print(rssi);
  //Serial.write("#");
  Serial.println('\n');
  
  delay(490);
}

void node0(){
 nodeid = 0x00; // node id
 rssi = 0;//random(-150, 0);  // rssi can be from noise floor to 0
 lat = -105.26; // DLC building
 lng = 40.01; // DLC building
 soil = random(0, 4096); // percentage from 0 to 4095
 /*if( (rssi > -104) || (lat != -105.26) || (lng != 40.01)){
  nodestatus = 0x01;
 }else{
  nodestatus = 0x00;
 }*/
 node_write(nodeid, rssi, lat, lng, soil);
}

void node1(){
 nodeid = 0x01; // node id
 rssi = random(-150, 0);  // rssi can be from noise floor to 0
 lat = -105.26; // DLC building
 lng = 40.01; // DLC building
 soil = 10;//random(0, 101); // percentage from 0 to 100
 /*if( (rssi > -104) || (lat != -105.26) || (lng != 40.01)){
  nodestatus = 0x01;
 }else{
  nodestatus = 0x00;
 }*/
 node_write(nodeid, rssi, lat, lng, soil);
}

void node2(){
 nodeid = 0x02; // node id
 rssi = random(-150, 0);  // rssi can be from noise floor to 0
 lat = -105.26; // DLC building
 lng = 40.01; // DLC building
 soil = random(0, 101); // percentage from 0 to 100
 /*if( (rssi > -104) || (lat != -105.26) || (lng != 40.01)){
  nodestatus = 0x01;
 }else{
  nodestatus = 0x00;
 }*/
 node_write(nodeid, rssi, lat, lng, soil);
}

void node3(){
 nodeid = 0x03; // node id
 rssi = random(-150, 0);  // rssi can be from noise floor to 0
 lat = -105.26; // DLC building
 lng = 40.01; // DLC building
 soil = 30;//random(0, 101); // percentage from 0 to 100
 /*if( (rssi > -104) || (lat != -105.26) || (lng != 40.01)){
  nodestatus = 0x01;
 }else{
  nodestatus = 0x00;
 }*/
 node_write(nodeid, rssi, lat, lng, soil);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial){
    ;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  node0();
  delay(5000);
  node1();
  delay(5000);
  node2();
  delay(5000);
  node3();
  delay(5000);
}







