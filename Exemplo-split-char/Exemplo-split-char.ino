String serialResponse = "";
char* sz = "BC9312KEF;03BT74NFD;12HB32UJE;14DA52QWE;85KJFGTYD;";

void setup()
{
 Serial.begin(9600);
 char *p = sz;
 char *str;
 while ((str = strtok_r(p, ";", &p)) != NULL) // delimiter is the semicolon
   Serial.println(str);

}

void loop()
{
if ( Serial.available()) {
 serialResponse = Serial.readStringUntil('\r\n');
 Serial.println(serialResponse);
}
}
