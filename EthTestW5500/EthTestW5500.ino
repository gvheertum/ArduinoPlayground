#include <SPI.h>
#include <Ethernet2.h>
#include <EthernetUdp2.h>
extern SPISettings wiznet_SPI_settings;

/*
Using eth on the SPI Line

Pin in Arduino
MOSI 11 or ICSP-4
MISO 12 or ICSP-1
SCLK 13 or ICSP-3
SCS 10
*/

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
unsigned long byteCount = 0;
unsigned int localPort = 8888;       // local port to listen for UDP packets

const char timeServer[] = "0.nl.pool.ntp.org"; // time.nist.gov NTP server

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
 
  SPISettings settingsA(8000000, MSBFIRST, SPI_MODE3);
  wiznet_SPI_settings = settingsA;

  // start the Ethernet connection and the server:
  if(Ethernet.begin(mac) == 0)
  {
    Serial.println("No eth with DHCP");

//    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
//      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
//    } else if (Ethernet.linkStatus() == LinkOFF) {
//      Serial.println("Ethernet cable is not connected.");
//    }
//    
    return;
  }
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  Udp.begin(localPort);
}

void loop() {
  // put your main code here, to run repeatedly:
  //getTime();

  getQuote();
  delay(30*1000);
  
}

EthernetClient client;
void getQuote() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  if (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // if ten seconds have passed since your last connection,
  // then connect again and send data:
    httpRequest();
 
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  Serial.println("starting request");
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect("192.168.123.235", 80)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    client.println("GET /QuoteClock/api/quote/get/ HTTP/1.1");
    client.println("Host: 192.168.123.235");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    Serial.println("Done with request!");
    // note the time that the connection was made:
    //lastConnectionTime = millis();
    delay(1000);
    
    int len = client.available();
    
    if (len > 0) {
      byte buffer[len];
      client.read(buffer, len);
      
        Serial.write(buffer, len); // show in the serial monitor (slows some boards)
      
      byteCount = byteCount + len;
    }else
    {
      Serial.print("No bytes!");
    }
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}



void getTime() {
  Serial.println("Going to send!");
  sendNTPpacket(timeServer); // send an NTP packet to a time server
  Serial.println("Package sent, awaiting");
  // wait to see if a reply is available
  delay(1000);
  Serial.println("Package waiting is over");
  if (Udp.parsePacket()) {
    Serial.println("WE HAVE DATA!");
    // We've received a packet, read the data from it
    Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    // the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, extract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    Serial.print("Seconds since Jan 1 1900 = ");
    Serial.println(secsSince1900);

    // now convert NTP time into everyday time:
    Serial.print("Unix time = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;
    // print Unix time:
    Serial.println(epoch);


    // print the hour, minute and second:
    Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
    Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
    Serial.print(':');
    if (((epoch % 3600) / 60) < 10) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    if ((epoch % 60) < 10) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.println(epoch % 60); // print the second
    
    // wait ten seconds before asking for the time again
    delay(10000);
  }
  else
  {
    Serial.println("NOOOO, no data!");
    delay(1000); // Wait one second if no data!
  }
  
  
  Ethernet.maintain();
}

// send an NTP request to the time server at the given address
void sendNTPpacket(const char * address) {
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Serial.println("Sending data");
  Serial.println(address);
  Udp.beginPacket(address, 123); // NTP requests are to port 123
  Serial.println("Writing data");
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Serial.println("Data written");
  Udp.endPacket();
  Serial.println("Jobs done!");
}
