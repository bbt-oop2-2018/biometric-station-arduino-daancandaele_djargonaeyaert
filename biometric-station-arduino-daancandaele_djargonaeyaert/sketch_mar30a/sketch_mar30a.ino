void setup() {
Serial.begin(115200);
Serial.println("hello world"); 

}

void loop() {
double waterlevel = 12.33;
int pubg = 1234;

Serial.print("[");
Serial.print(waterlevel);
Serial.print("|");
Serial.print(pubg);
Serial.println("]");
delay(1000);
}
