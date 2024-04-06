int bomb=2;
int flama1=4;
int tierra1=15;


int a,b,c,d,f;

void setup() {
  pinMode(flama1, INPUT);
  pinMode(tierra1, INPUT);
  pinMode(bomb, OUTPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() 
{
        flama();
        tierra();
        float fuego = a;
        String data = "{\"Fuego\": " + String(fuego) + "}";
        Serial.println(data);
        delay(10);
        float thumedad = b;
        String data2 = "{\"THumedad\": " + String(thumedad) + "}";
        Serial.println(data2);
        delay(500);
        if (fuego>=35)
        {
        digitalWrite(bomb,HIGH);
        delay(200);
        digitalWrite(bomb,LOW); 
        }
}

void flama()
{
  a=analogRead(flama1);
  delay(200);
 a=map(a,4095,0,0,100);
}

void tierra()
{
  b=analogRead(tierra1);
  delay(200);
  b=map(b,4095,0,0,100);
}
