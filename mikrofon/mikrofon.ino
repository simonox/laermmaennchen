int currentValue;
int maxValue;
int minValue;
unsigned long timer;
int sampleSpan = 5; // Amount in milliseconds to sample data
int volume; // this roughly goes from 0 to 700

void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600); 
    resetValues();
}

void loop() 
{
    currentValue = analogRead(A0);

    if (currentValue < minValue) {
        minValue = currentValue;
    } 
    if (currentValue > maxValue) {
        maxValue = currentValue;
    }

    if (millis() - timer >= sampleSpan) {
        volume = maxValue - minValue;

        Serial.println(volume);
        if (volume > 10) {
          digitalWrite(LED_BUILTIN, HIGH);
        } else {
          digitalWrite(LED_BUILTIN, LOW);
        }

        resetValues();
    }
}

void resetValues()
{
    maxValue = 0;
    minValue = 40;
    timer = millis(); 
}
