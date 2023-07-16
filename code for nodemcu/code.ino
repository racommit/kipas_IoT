#define BLYNK_TEMPLATE_ID "TMPL6rboYfNoI"
#define BLYNK_TEMPLATE_NAME "Fan IoT"
#define BLYNK_AUTH_TOKEN "nR6uqcqGmfoyHcAxwaiih-EaOLaoTuEL"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT22.h>


char ssid[] = "Desember kita";
char pass[] = "235689124";
//define pin data
#define data D2

bool relay = true;
int pin = 7; 
bool lock = true;
bool kondisi = true;
int saklar = 0;
int saklar2 = 0;
float t;
float h;

DHT22 dht22(data); 
 
void setup() {
  Serial.begin(9600); //1bit=10µs
  // Serial.println("\ntest capteur DTH22");
  
  

  digitalWrite(relay, LOW);
  digitalWrite(lock, LOW);
  // digitalWrite(lock, LOW);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  //Serial.println(dht22.debug()); //optionnal
  Serial.println(relay);
  Blynk.run();
  t = dht22.getTemperature();
  h = dht22.getHumidity();

  // Serial.println(dht22.getLastError());
  Blynk.virtualWrite(V0, t);
   

  // kondisi();
  // Serial.print(" kondisi saklar :");
  // Serial.println(saklar);
  // Serial.print(" kondisi kunci : ");Serial.println(lock);
  // Serial.print(" kondisi saklar2 :");Serial.print(saklar2);
  
  if(saklar == 1){
    lock = true;
  }else if(saklar == 0){
    lock = false;
    relay = false;
    // Serial.print("saklar mati");
    Blynk.virtualWrite(V2, LOW);
    // Serial.print(" Kipas mati ");
    // kondisi2();
  }

  if(saklar2 == 1){
    kondisi = true;
  }else if(saklar2 == 0){
    kondisi = false;
  }



  if(lock == true){
    if(kondisi == true){
      // Serial.print("pengkondisian nyala");
        if(t > 32){
              relay = true;
              Blynk.virtualWrite(V2, HIGH);
              // Serial.print(" Kipas nyala ");
            }else if(t < 31){
              relay = false;
              Blynk.virtualWrite(V2, LOW);
              // Serial.print(" Kipas mati ");
            }
              // Serial.print(" t= ");
              // Serial.print(t);
      }else if(kondisi == false){
              relay = true;
              Blynk.virtualWrite(V2, HIGH);
              // Serial.print(" Kipas nyala ");
              // Serial.print("pengkondisian mati");
      }  
  }else if(lock == false){
          relay = false;
          Blynk.virtualWrite(V2, LOW);
          // Serial.print(" Kipas mati ");
  }

  
}

BLYNK_WRITE(V1){
  saklar = param.asInt();
}

BLYNK_WRITE(V3){
  saklar2 = param.asInt();
}









