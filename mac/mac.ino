static char macString[18];
static int t = 0;
static bool printed = false;

void setup() {
    Spark.variable("mac", macString, STRING);
    Serial.begin(115200);

    byte mac[6];
    WiFi.macAddress(mac);
    sniprintf(macString, 18, "%02x:%02x:%02x:%02x:%02x:%02x",
        mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
}

void loop() {
    int delta = millis() - t;
    if (delta > 10000) {
        Spark.publish("mac", macString, 0, PRIVATE);
        printed = false;
        t = millis();
    } else if (delta > 5000 && !printed) {
        Serial.println(macString);
        printed = true;
    }
}
