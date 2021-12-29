/*********************************************
 * @file MQTT_utilites.c                     *
 * @brief MQTT_utilites Details              *
 * Copyright (c) 2020 E-Vision Corp.         *
 * Created     : 21/08/2020 10:22:38         *
 * Contributors: Ahmed_Gad && Khalid_Ibrahim *
 * Version     : v_01                        *
 * Edit By     :                             *
 * Edit Reason :                             *
 * ******************************************/

#include"MQTT_utilites.h"

unsigned short int String_Length(char * Ptr_String) {

	unsigned short int StringIndex = 0;

	while ( (Ptr_String != (void*) 0 ) && *(Ptr_String + StringIndex) !=  '\0') {

		StringIndex++;
	}

	return StringIndex;
}

unsigned char String_Copy(char * Ptr_Source, char * Ptr_Destination) {

	unsigned short int DestIndex = 0;

	while ( (Ptr_Destination != (void*) 0 )&& *(Ptr_Destination + DestIndex) !=  '\0') {

		*(Ptr_Source) = *(Ptr_Destination + DestIndex);
		DestIndex++;
		Ptr_Source++;
	}
	return DestIndex;
}

void Memory_Copy(char * Ptr_Source, char * Ptr_Destination,
		unsigned short int DestinationSize) {
	unsigned short int DestIndex = 0;

	while ((DestIndex) < DestinationSize) {

		*(Ptr_Source) = *(Ptr_Destination + DestIndex);
		DestIndex++;
		Ptr_Source++;
	}

}

unsigned char MQTT_Encode_RemLength(char *PacketControl_Ptr, int PayLoad_length) {

unsigned char RemindLengthBytes=0;


	do {
		char d = PayLoad_length % 128;
		PayLoad_length /= 128;
		/* if there are more digits to encode, set the top bit of this digit */
		if (PayLoad_length > 0)
			d |= 0x80; // OR with 128
		*PacketControl_Ptr = d;
		PacketControl_Ptr++;
		RemindLengthBytes++;

	} while (PayLoad_length > 0);

	return RemindLengthBytes;
}

