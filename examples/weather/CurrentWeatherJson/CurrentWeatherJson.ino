#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

bool connectWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(OFFBEAT_WIFI_SSID, OFFBEAT_WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  return true;
}

// tag::weather-current-json-docs[]
void sendWeatherRequest(WebSocketsClient& socket) {
  StaticJsonDocument<192> request;
  request["weather"]["city"] = "Copenhagen";

  String body;
  serializeJson(request, body);
  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=weather");
}

void handleWeatherResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<2048> response;
  DeserializationError error = deserializeJson(response, payload, length);
  if (error) {
    Serial.println("Unable to parse weather response");
    return;
  }

  JsonObject weather = response["weather.response"];
  if (weather.isNull()) {
    Serial.println("No weather.response payload");
    return;
  }

  Serial.print("Location: ");
  Serial.println(weather["location"]["name"].as<const char*>());
  Serial.print("Temperature C: ");
  Serial.println(weather["current"]["temp_c"].as<float>());
  Serial.print("Wind km/h: ");
  Serial.println(weather["current"]["wind_kph"].as<float>());
  Serial.print("WeatherAPI condition code: ");
  Serial.println(weather["current"]["condition"]["code"].as<int>());
  Serial.println("TEST:PASS");
}
// end::weather-current-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  if (type == WStype_CONNECTED) {
    sendWeatherRequest(webSocket);
  } else if (type == WStype_TEXT) {
    handleWeatherResponse(payload, length);
  }
}

void setup() {
  Serial.begin(115200);
  if (!connectWifi()) {
    return;
  }
  webSocket.begin(OFFBEAT_WS_HOST, OFFBEAT_WS_PORT, OFFBEAT_WS_PATH);
  webSocket.onEvent(websocketEvent);
  webSocket.setReconnectInterval(5000);
}

void loop() {
  webSocket.loop();
}
