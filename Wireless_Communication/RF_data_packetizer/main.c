#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
Structs are copied directly from the CC13x2 SimpleLink API
*/
//! \brief Structure for the TX Packet
typedef struct {
	uint8_t dstAddr[8];              //!<  Destination address
	uint32_t absTime;                //!< Absolute time to Tx packet (0 for immediate)
	//!< Layer will use last SeqNum used + 1

	uint8_t len;                     //!< Payload Length
	uint8_t payload[128];       //!< Payload
} EasyLink_TxPacket;

//! \brief Structure for the RX'ed Packet
typedef struct {
	uint8_t dstAddr[8];              //!< Dst Address of RX'ed packet
	int8_t rssi;                     //!< rssi of RX'ed packet
	uint32_t absTime;                //!< Absolute time to turn on Rx when passed
	//!< (0 for immediate), Or Absolute time that packet was Rx
	//!< when returned.

	uint32_t rxTimeout;              //!< Relative time in ticks from Rx start to Rx TimeOut
	//!< a value of 0 means no timeout
	uint8_t len;                     //!< length of RX'ed packet
	uint8_t payload[128]; //!< payload of RX'ed packet
} EasyLink_RxPacket;

/*
Structs are custom made or modified from the EasyLink API
*/
//! \brief Structure for the TX Packet Payload
struct Message_Packet_tx {
	uint32_t message_str[32];   //!< 32 bit unsigned integer array containing ascii characters to create a char string
	uint8_t message_str_len;    //!< 8 bit unsigned integer containing character length of message_str
	uint32_t message_num[32];   //!< 32 bit unsigned integer array containing numbers up to 0xFFFFFFF
	float message_float[16];    //!< float array containing float characters
	uint32_t message_float_conv[16];    //!< 32 bit unsigned integer array containing integer conversion of a message_float
};

//! \brief Structure for the RX'ed Packet Payload
struct Message_Packet_rx {
	char message_str[32];   //!< char array to contain an integer array up to 32 chars (limit TBD)
	uint8_t message_str_len; //!< 8 bit unsigned integer containing character length of message_str
	uint32_t message_num;   //!< 32 bit unisgned integer containing a number up to 0xFFFFFFF
	float message_float;    //!< float number
	uint32_t message_float_conv;    //!< float converted to an int
};

//! \brief Structure to access the EasyLink API Rx/Tx typedef structs
struct RadioOperation {
	EasyLink_TxPacket easyLinkTxPacket;
	EasyLink_RxPacket easyLinkRxPacket;
};

//! \brief global initialization of the above struct
struct RadioOperation currentRadioOperation;

//! \brief function to package payload data from Message_Packet_tx object for Tx
size_t package_data(struct Message_Packet_tx sen) {

    // Push message payload content into Tx Packet via bit-shifting
	currentRadioOperation.easyLinkTxPacket.payload[0] = (sen.message_str[0] & 0xFF000000) >> 24;
	currentRadioOperation.easyLinkTxPacket.payload[1] = (sen.message_str[0] & 0x00FF0000) >> 16;
	currentRadioOperation.easyLinkTxPacket.payload[2] = (sen.message_str[0] & 0xFF00) >> 8;
	currentRadioOperation.easyLinkTxPacket.payload[3] = (sen.message_str[0]) & 0xFF;

	currentRadioOperation.easyLinkTxPacket.payload[4] = (sen.message_str[1] & 0xFF000000) >> 24;
	currentRadioOperation.easyLinkTxPacket.payload[5] = (sen.message_str[1] & 0x00FF0000) >> 16;
	currentRadioOperation.easyLinkTxPacket.payload[6] = (sen.message_str[1] & 0xFF00) >> 8;
	currentRadioOperation.easyLinkTxPacket.payload[7] = (sen.message_str[1]) & 0xFF;

	currentRadioOperation.easyLinkTxPacket.payload[8] = (sen.message_str[2] & 0xFF000000) >> 24;
	currentRadioOperation.easyLinkTxPacket.payload[9] = (sen.message_str[2] & 0x00FF0000) >> 16;
	currentRadioOperation.easyLinkTxPacket.payload[10] = (sen.message_str[2] & 0xFF00) >> 8;
	currentRadioOperation.easyLinkTxPacket.payload[11] = (sen.message_str[2]) & 0xFF;

	currentRadioOperation.easyLinkTxPacket.payload[12] = (sen.message_str_len);

	currentRadioOperation.easyLinkTxPacket.payload[13] = (sen.message_num[0] & 0xFF000000) >> 24;
	currentRadioOperation.easyLinkTxPacket.payload[14] = (sen.message_num[0] & 0x00FF0000) >> 16;
	currentRadioOperation.easyLinkTxPacket.payload[15] = (sen.message_num[0] & 0xFF00) >> 8;
	currentRadioOperation.easyLinkTxPacket.payload[16] = (sen.message_num[0]) & 0xFF;

	currentRadioOperation.easyLinkTxPacket.payload[17] = (sen.message_float_conv[0] & 0xFF000000) >> 24;
	currentRadioOperation.easyLinkTxPacket.payload[18] = (sen.message_float_conv[0] & 0x00FF0000) >> 16;
	currentRadioOperation.easyLinkTxPacket.payload[19] = (sen.message_float_conv[0] & 0xFF00) >> 8;
	currentRadioOperation.easyLinkTxPacket.payload[20] = (sen.message_float_conv[0]) & 0xFF;

	currentRadioOperation.easyLinkTxPacket.len = sizeof(struct Message_Packet_tx);

	return 0;
}


//! \brief function to decode payload data from easyLinkRxPacket object
size_t decode_data(struct Message_Packet_rx con) {

    // Get string length from payload
    con.message_str_len = (currentRadioOperation.easyLinkRxPacket.payload[12]);
    size_t length = con.message_str_len;

    // Push contents of payload into char array
	for(int i = 0; i < length; i++){
        con.message_str[i] = (currentRadioOperation.easyLinkRxPacket.payload[i]);
	}

    // Push contents of payload array into a uint32 integer via bit-shifting
	con.message_num = (currentRadioOperation.easyLinkRxPacket.payload[13] << 24) | (currentRadioOperation.easyLinkRxPacket.payload[14] << 16) | (currentRadioOperation.easyLinkRxPacket.payload[15] << 8) | (currentRadioOperation.easyLinkRxPacket.payload[16]);

	// Push contents of payload array into a uint32 integer via bit-shifting
	con.message_float_conv = (currentRadioOperation.easyLinkRxPacket.payload[17] << 24) | (currentRadioOperation.easyLinkRxPacket.payload[18] << 16) | (currentRadioOperation.easyLinkRxPacket.payload[19] << 8) | (currentRadioOperation.easyLinkRxPacket.payload[20]);

    // Convert above integer into float
	con.message_float = (float) con.message_float_conv / 1000000;

	printf("\n\nDecoded string: %s\n", con.message_str);
	printf("Decoded string char length: %d\n", con.message_str_len);
	printf("Decoded number: %x\n", con.message_num);
	printf("Decoded converted float: %d\n", con.message_float_conv);
	printf("Decoded float: %f\n", con.message_float);

	return 0;
}


int main() {

	struct Message_Packet_tx sensor;    // Message_Packet_tx object (for transmitting)
	struct Message_Packet_rx concentrator; // Message_Packet_rx object (for receiving)

	/* Load data into sensor message payload */
	// 4 ascii chars per array value (uint8)
	sensor.message_str[0] = 'hell';
	sensor.message_str[1] = 'o wo';
	sensor.message_str[2] = 'rld!';
	// Length of above message string
	sensor.message_str_len = 12;
	// Message number from 0 to 0xFFFFFFF
	sensor.message_num[0] = 0xABCDEF1;
	// Message float up to 7 digits
	sensor.message_float[0] = 1.234567;
	// integer conversion of above float
	sensor.message_float_conv[0] = sensor.message_float[0] * 1000000;

	// Package payload data from sensor object for Tx
	package_data(sensor);

	printf("Size of payload is %d\n", currentRadioOperation.easyLinkTxPacket.len);

    // Print contents of unformatted payload data
	printf("Payload string: \n");
	printf("%c", currentRadioOperation.easyLinkTxPacket.payload[0]);
	printf("%c", currentRadioOperation.easyLinkTxPacket.payload[1]);
	printf("%c", currentRadioOperation.easyLinkTxPacket.payload[2]);
	printf("%c", currentRadioOperation.easyLinkTxPacket.payload[3]);
	printf("\n");

	printf("%c", currentRadioOperation.easyLinkTxPacket.payload[4]);
	printf("%c", currentRadioOperation.easyLinkTxPacket.payload[5]);
	printf("%c", currentRadioOperation.easyLinkTxPacket.payload[6]);
	printf("%c", currentRadioOperation.easyLinkTxPacket.payload[7]);
	printf("\n");

	printf("%c", currentRadioOperation.easyLinkTxPacket.payload[8]);
	printf("%c", currentRadioOperation.easyLinkTxPacket.payload[9]);
	printf("%c", currentRadioOperation.easyLinkTxPacket.payload[10]);
	printf("%c", currentRadioOperation.easyLinkTxPacket.payload[11]);
	printf("\n");

	printf("Payload string char length: \n");
	printf("%d", currentRadioOperation.easyLinkTxPacket.payload[12]);
	printf("\n");

	printf("Payload num: \n");
	printf("%x", currentRadioOperation.easyLinkTxPacket.payload[13]);
	printf("%x", currentRadioOperation.easyLinkTxPacket.payload[14]);
	printf("%x", currentRadioOperation.easyLinkTxPacket.payload[15]);
	printf("%x", currentRadioOperation.easyLinkTxPacket.payload[16]);
	printf("\n");

	printf("Payload float: \n");
	printf("%x", currentRadioOperation.easyLinkTxPacket.payload[17]);
	printf("%x", currentRadioOperation.easyLinkTxPacket.payload[18]);
	printf("%x", currentRadioOperation.easyLinkTxPacket.payload[19]);
	printf("%x", currentRadioOperation.easyLinkTxPacket.payload[20]);

    // Simulate actual sensor RF transmission to concentrator
	currentRadioOperation.easyLinkRxPacket.payload[0] = currentRadioOperation.easyLinkTxPacket.payload[0];
	currentRadioOperation.easyLinkRxPacket.payload[1] = currentRadioOperation.easyLinkTxPacket.payload[1];
	currentRadioOperation.easyLinkRxPacket.payload[2] = currentRadioOperation.easyLinkTxPacket.payload[2];
	currentRadioOperation.easyLinkRxPacket.payload[3] = currentRadioOperation.easyLinkTxPacket.payload[3];

	currentRadioOperation.easyLinkRxPacket.payload[4] = currentRadioOperation.easyLinkTxPacket.payload[4];
	currentRadioOperation.easyLinkRxPacket.payload[5] = currentRadioOperation.easyLinkTxPacket.payload[5];
	currentRadioOperation.easyLinkRxPacket.payload[6] = currentRadioOperation.easyLinkTxPacket.payload[6];
	currentRadioOperation.easyLinkRxPacket.payload[7] = currentRadioOperation.easyLinkTxPacket.payload[7];

	currentRadioOperation.easyLinkRxPacket.payload[8] = currentRadioOperation.easyLinkTxPacket.payload[8];
	currentRadioOperation.easyLinkRxPacket.payload[9] = currentRadioOperation.easyLinkTxPacket.payload[9];
	currentRadioOperation.easyLinkRxPacket.payload[10] = currentRadioOperation.easyLinkTxPacket.payload[10];
	currentRadioOperation.easyLinkRxPacket.payload[11] = currentRadioOperation.easyLinkTxPacket.payload[11];

	currentRadioOperation.easyLinkRxPacket.payload[12] = currentRadioOperation.easyLinkTxPacket.payload[12];

	currentRadioOperation.easyLinkRxPacket.payload[13] = currentRadioOperation.easyLinkTxPacket.payload[13];
	currentRadioOperation.easyLinkRxPacket.payload[14] = currentRadioOperation.easyLinkTxPacket.payload[14];
	currentRadioOperation.easyLinkRxPacket.payload[15] = currentRadioOperation.easyLinkTxPacket.payload[15];
	currentRadioOperation.easyLinkRxPacket.payload[16] = currentRadioOperation.easyLinkTxPacket.payload[16];

	currentRadioOperation.easyLinkRxPacket.payload[17] = currentRadioOperation.easyLinkTxPacket.payload[17];
	currentRadioOperation.easyLinkRxPacket.payload[18] = currentRadioOperation.easyLinkTxPacket.payload[18];
	currentRadioOperation.easyLinkRxPacket.payload[19] = currentRadioOperation.easyLinkTxPacket.payload[19];
	currentRadioOperation.easyLinkRxPacket.payload[20] = currentRadioOperation.easyLinkTxPacket.payload[20];

    // Decode payload data Rx'ed by concentrator object
	decode_data(concentrator);

	return 0;
}
