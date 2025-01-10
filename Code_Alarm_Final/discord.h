#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>

const char ssid[] = "#####";    // Network SSID (name)
const char pass[] = "#####";    // Network password (use for WPA, or use as key for WEP)

const char server[] = "discordapp.com";
const int port = 443;
const String discord_webhook = "/api/webhooks/1325332605637496943/VZZy1uo-JqLtltkl_1pDUa4Bh8yFqyh7CxicRaOkXoJImugGQZ5bGRqX_Z7hoqN8YRvP";
const String discord_tts = "true";

int status = WL_IDLE_STATUS;
WiFiSSLClient client;
HttpClient http_client = HttpClient(client, server, port);

void connectWIFI() {
  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("[WiFi] Connecting to: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(100);
  }

  // you're connected now, so print out the data:
  Serial.println("[WiFi] Connected");
}

void discord_send(String content) {
  Serial.println("[HTTP] Connecting to Discord...");
  Serial.println("[HTTP] Message: " + content);
  Serial.println("[HTTP] TTS: " + discord_tts);
  http_client.post(discord_webhook, "application/json", "{\"content\":\"" + content + "\", \"tts\":" + discord_tts + "}");
  // read the status code and body of the response
  int statusCode = http_client.responseStatusCode();
  String response = http_client.responseBody();

  Serial.print("[HTTP] Status code: ");
  Serial.println(statusCode);
  Serial.print("[HTTP] Response: ");
  Serial.println(response);
}
