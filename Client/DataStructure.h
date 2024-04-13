
//166 Read With 249 bytes
constexpr unsigned short PACKET_SIZE = 249;
char packet_buffer[PACKET_SIZE];

union {
  byte b[4];
  short d[2];
} compression;

//Take value from 0 to 4096
//Compress 2, 12 bits input to  3, 8 bits output 
void WriteBuffer(const unsigned short& index){
  packet_buffer[index * 3] = compression.b[0]; // First 8 bits of data0
  packet_buffer[(index * 3) + 1] = compression.b[2]; // First 8 bits of data1

  // Last 4 bits of data0 and data1
  packet_buffer[(index * 3) + 2] = compression.b[1] | (compression.b[3] << 4);
}

void ReadBuffer(const unsigned short& index) {
  compression.b[0] = packet_buffer[index * 3];
  compression.b[1] = packet_buffer[(index * 3) + 2] & 0b00001111;

  compression.b[2] = packet_buffer[(index * 3) + 1];
  compression.b[3] = packet_buffer[(index * 3) + 2] >> 4;
}