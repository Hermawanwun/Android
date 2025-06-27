#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define WIFI_SSID "Network_id"
#define WIFI_PASSWORD "FS1A06050"
#define FIREBASE_HOST "my-application-new-28e2a-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "e4rqfcimaujWr62ciPkutDtACGHqs4Qww2FXU81D"

// Buat objek config dan auth
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// Pin relay
int relay1 = D1;
int relay2 = D2;
int relay3 = D3;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Menghubungkan WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi terhubung");
  Serial.println(WiFi.localIP());

  // Konfigurasi Firebase
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Atur pin sebagai output
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);

}

void loop() {
  
  // Baca data dari Firebase
  if (Firebase.getInt(firebaseData, "/STATUS_LAMPU")) {
    int statusLampu = firebaseData.intData();
    digitalWrite(relay1, statusLampu == 1 ? HIGH : LOW);
    Serial.println("Lampu: " + String(statusLampu));
  }

  // KOMPUTER
  if (Firebase.getInt(firebaseData, "/STATUS_KOMPUTER")) {
    int statusKomputer = firebaseData.intData();
    digitalWrite(relay2, statusKomputer == 1 ? HIGH : LOW);
    Serial.println("Komputer: " + String(statusKomputer));
  }

  // PUMP
  if (Firebase.getInt(firebaseData, "/STATUS_PUMP")) {
    int statusPump = firebaseData.intData();
    digitalWrite(relay3, statusPump == 1 ? HIGH : LOW);
    Serial.println("Pompa: " + String(statusPump));
  }


  delay(500);
}
