// void setup()
// {
//   Serial.begin(115200);

//   CBORPair data = CBORPair(100);

//   CBORPair tagCBOR = CBORPair(100);
//   CBORPair tagCBOR2 = CBORPair(100);
//   CBORPair gpsCBOR = CBORPair(100);

//   Serial.println("JSON Representation of message");
//   Serial.println("{");
//   Serial.println("\t\"stdnts\": [");
//   Serial.println("\t\t{\"id\": \"00:11:22:33:FF:EE\",");
//   Serial.println("\t\t \"rssi\": -80},");
//   Serial.println("\t\t{\"id\": \"00:8F:AB:3F:FE:AC\",");
//   Serial.println("\t\t \"rssi\": -90}],");
//   Serial.println("\t\"gps\": {");
//   Serial.println("\t\t\"lat\": 38.8951,");
//   Serial.println("\t\t\"lng\": -77.0364,");
//   Serial.println("\t\t},");
//   Serial.println("\t\"pir\": \"true\",");
//   Serial.println("\t\"acceleration\": \"45\",");
//   Serial.println("}");

//   tagCBOR.append("id", "00:11:22:33:FF:EE");
//   tagCBOR.append("rssi", -80);
//   tagCBOR2.append("id", "00:8F:AB:3F:FE:AC");
//   tagCBOR2.append("rssi", -90);

//   gpsCBOR.append("lat", 38.8951);
//   gpsCBOR.append("lng", -77.0364);

//   CBORArray tags = CBORArray(20);
//   tags.append(tagCBOR);
//   tags.append(tagCBOR2);

//   data.append("stdnts", tags);
//   data.append("gps", gpsCBOR);
//   data.append("pir", "true");
//   data.append("acceleration", 45);
//   // That's it! Let's see how our data looks.
//   Serial.println("CBOR Encoded data:");
//   const uint8_t *cbor_encoded = data.to_CBOR();
//   for (size_t i = 0; i < data.length(); ++i)
//   {
//     if (cbor_encoded[i] < 0x10)
//     {
//       Serial.print('0');
//     }
//     Serial.print(cbor_encoded[i], HEX);
//   }
//   Serial.println("\n You can check this encoding using http://cbor.me");
// }

// void loop()
// {
// }