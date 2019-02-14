int nodeid = 0;
int nodestatus = 0;
int rssi = 0;
float lat = 0;
float lng = 0;
int soil = 0;

void node_write(int nodeid, int rssi, int nodestatus, float lat, float lng, int soil){
  Serial.write("NodeId:");
  Serial.println(nodeid, HEX);
  Serial.write("RSSI:");
  Serial.println(rssi);
  Serial.write("Status:");
  Serial.println(nodestatus, HEX);
  Serial.write("Latitude:");
  Serial.println(lat);
  Serial.write("Longitude:");
  Serial.println(lng);
  Serial.write("SoilMoisture:");
  Serial.println(soil);
  delay(490);
}

void node1(){
 nodeid = 0x01; // node id
 rssi = random(-150, 0);  // rssi can be from noise floor to 0
 lat = -105.26; // DLC building
 lng = 40.01; // DLC building
 soil = random(0, 101); // percentage from 0 to 100
 if( (rssi > -104) || (lat != -105.26) || (lng != 40.01)){
  nodestatus = 0x01;
 }else{
  nodestatus = 0x00;
 }
 node_write(nodeid, rssi, nodestatus, lat, lng, soil);
}

void node2(){
 nodeid = 0x02; // node id
 rssi = random(-150, 0);  // rssi can be from noise floor to 0
 lat = -105.26; // DLC building
 lng = 40.01; // DLC building
 soil = random(0, 101); // percentage from 0 to 100
 if( (rssi > -104) || (lat != -105.26) || (lng != 40.01)){
  nodestatus = 0x01;
 }else{
  nodestatus = 0x00;
 }
 node_write(nodeid, rssi, nodestatus, lat, lng, soil);
}

void node3(){
 nodeid = 0x03; // node id
 rssi = random(-150, 0);  // rssi can be from noise floor to 0
 lat = -105.26; // DLC building
 lng = 40.01; // DLC building
 soil = random(0, 101); // percentage from 0 to 100
 if( (rssi > -104) || (lat != -105.26) || (lng != 40.01)){
  nodestatus = 0x01;
 }else{
  nodestatus = 0x00;
 }
 node_write(nodeid, rssi, nodestatus, lat, lng, soil);
}

void node4(){
 nodeid = 0x04; // node id
 rssi = random(-150, 0);  // rssi can be from noise floor to 0
 lat = -105.26; // DLC building
 lng = 40.01; // DLC building
 soil = random(0, 101); // percentage from 0 to 100
 if( (rssi > -104) || (lat != -105.26) || (lng != 40.01)){
  nodestatus = 0x01;
 }else{
  nodestatus = 0x00;
 }
 node_write(nodeid, rssi, nodestatus, lat, lng, soil);
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
  node1();
  node2();
  node3();
  node4();
}







