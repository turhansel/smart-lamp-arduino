#include <SoftwareSerial.h>
SoftwareSerial btConnect(0, 1);
int ses_sensoru = 2;
int role = 3;
int alkis = 0;

long algilama_araligi_baslangic = 0;
long algilama_araligi = 0;
boolean isik_durumu = false;

void setup() 
{
  btConnect.begin(9600); /* Bluetooth haberleşmesi */
  pinMode(ses_sensoru, INPUT);
  pinMode(role, OUTPUT);
}
char data; /* okunan verilerin kaydedileceği değişken */
void loop() 
{
  
int sensor_durumu = digitalRead(ses_sensoru);
 if (sensor_durumu == 0)
  {
    if (alkis == 0)
  {
algilama_araligi_baslangic = algilama_araligi = millis();
      alkis++;
    }
    else if (alkis > 0 && millis()-algilama_araligi >= 50)
    {
      algilama_araligi = millis();
      alkis++;
    }
    }
 if (millis()-algilama_araligi_baslangic >= 400)
  {
    if (alkis == 2)
    {
      if (!isik_durumu)
        {
          isik_durumu = true;
          digitalWrite(role, HIGH);
        }
        else if (isik_durumu)
        {
          isik_durumu = false;
          digitalWrite(role, LOW);
        }
    }
    alkis = 0;
  }
while (btConnect.available() > 0) { /* Yeni veri var mı */
    data = btConnect.read(); /* Yeni veriyi btConnect degiskenine kaydet */
    switch (data) { /* Okunan karaktere göre işlem yap */
      case 'o': /* gelen karakterin işlem karşılığı */
        digitalWrite(role, HIGH);
        break;
      case 'c':
        digitalWrite(role, LOW);
        break;
    }
}
}
  
