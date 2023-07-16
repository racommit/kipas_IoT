int relay = 7;
void setup() {
  Serial.begin(9600); // Baudrate 9600bps
  pinMode(relay, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    // Membaca data dari NodeMCU
    String receivedData = Serial.readStringUntil('\n');
    int myInt = receivedData.toInt();
    // Lakukan sesuatu dengan data yang diterima
      
    
    Serial.print(myInt);

    if(myInt == 1){
      digitalWrite(relay, LOW);
    }else if(myInt == 0){
      digitalWrite(relay, HIGH);
    }
  }
}
