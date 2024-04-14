
constexpr uint8_t mac_01[] = {0x84, 0xCC, 0xA8, 0x61, 0x01, 0x4C};

//166 Read With 249 bytes
constexpr unsigned short PACKET_SIZE = 249;

struct Data{
  char flags; //1 bytes
  char packet_buffer[PACKET_SIZE]; //249 bytes
} data; //250 bytes out of 250 for message

union {
  byte b[4];
  short d[2];
} compression;

//Take value from 0 to 4096
//Compress 2, 12 bits input to  3, 8 bits output 
void WriteBuffer(const unsigned short& index){
  data.packet_buffer[index * 3] = compression.b[0]; // First 8 bits of data0
  data.packet_buffer[(index * 3) + 1] = compression.b[2]; // First 8 bits of data1

  // Last 4 bits of data0 and data1
  data.packet_buffer[(index * 3) + 2] = compression.b[1] | (compression.b[3] << 4);
}

void ReadBuffer(const unsigned short& index) {
  compression.b[0] = data.packet_buffer[index * 3];
  compression.b[1] = data.packet_buffer[(index * 3) + 2] & 0b00001111;

  compression.b[2] = data.packet_buffer[(index * 3) + 1];
  compression.b[3] = data.packet_buffer[(index * 3) + 2] >> 4;
}