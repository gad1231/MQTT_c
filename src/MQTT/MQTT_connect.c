/**************************************************
 * @file MQTT_ControlPacket.c                     *
 * @brief MQTT_ControlPacket Detiles              *
 * Copyright (c) 2020 E-Vision Corp.               *
 * Created     : 21/08/2020 10:22:38               *
 * Contributors: Ahmed_Gad && Khalid_Ibrahim       *
 * Version     : v_01                              *
 * Edit By     :                                   *
 * Edit Reason :                                   *
 * ************************************************/

#include "MQTT_connect.h"



int MQTT_Connect(char *PacketControl_Arr,
		MQTT_ConnectPacketControl_s *PacketControl) {

	int s32PayloadLen = 0;
	unsigned short int u16PacketControlIndex = 0;

	PacketControl->Header.Bits.PacketType = CONNECT;
	PacketControl_Arr[u16PacketControlIndex++] = PacketControl->Header.Bytes[0];

	PacketControl->Parammeters.ClientID.Length = String_Length(
			PacketControl->Parammeters.ClientID.Ptr);
	PacketControl->Parammeters.WillTopicName.Length = String_Length(
			PacketControl->Parammeters.WillTopicName.Ptr);
	PacketControl->Parammeters.WillMessage.Length = String_Length(
			PacketControl->Parammeters.WillMessage.Ptr);
	PacketControl->Parammeters.Username.Length = String_Length(
			PacketControl->Parammeters.Username.Ptr);
	PacketControl->Parammeters.Password.Length = String_Length(
			PacketControl->Parammeters.Password.Ptr);

	s32PayloadLen = CONNECT_VARIABLE_HEADER_BYTES;

	s32PayloadLen+= (PacketControl->Parammeters.ClientID.Ptr)?PacketControl->Parammeters.ClientID.Length+2:0;
	s32PayloadLen+= (PacketControl->ConnectFlags.Bit.WillFlag)? PacketControl->Parammeters.WillTopicName.Length+2:0;
	s32PayloadLen+= (PacketControl->ConnectFlags.Bit.WillFlag)? PacketControl->Parammeters.WillMessage.Length+2:0;
	s32PayloadLen+= (PacketControl->ConnectFlags.Bit.UserNameFlag)? PacketControl->Parammeters.Username.Length+2:0;
	s32PayloadLen+= (PacketControl->ConnectFlags.Bit.PasswordFlag)? PacketControl->Parammeters.Password.Length+2:0;



	PacketControl_Arr[u16PacketControlIndex++] =s32PayloadLen;


	Memory_Copy(&PacketControl_Arr[u16PacketControlIndex],
			PacketControl->ProtocolName, PROTOCOL_NAME_SIZE);
	u16PacketControlIndex = u16PacketControlIndex + PROTOCOL_NAME_SIZE;

	PacketControl_Arr[u16PacketControlIndex++] = PacketControl->ProtocolLevel;

	PacketControl_Arr[u16PacketControlIndex++] =
			PacketControl->ConnectFlags.Byte;

	PacketControl_Arr[u16PacketControlIndex++] =
			(PacketControl->keepAliveInterval) / 256;
	PacketControl_Arr[u16PacketControlIndex++] =
			(PacketControl->keepAliveInterval) % 256;

	/*
	 * Comment Section Describe Replacements between Strlen & Strcpy Std Fun To MQtt_Func
	 */
	PacketControl_Arr[u16PacketControlIndex++] =
			(PacketControl->Parammeters.ClientID.Length) / 256;
	PacketControl_Arr[u16PacketControlIndex++] =
			(PacketControl->Parammeters.ClientID.Length) % 256;

	u16PacketControlIndex += String_Copy(
			&PacketControl_Arr[u16PacketControlIndex],
			PacketControl->Parammeters.ClientID.Ptr);

	if ((PacketControl->ConnectFlags.Bit.WillFlag) != 0) {

		PacketControl_Arr[u16PacketControlIndex++] =
				(PacketControl->Parammeters.WillTopicName.Length) / 256;
		PacketControl_Arr[u16PacketControlIndex++] =
				(PacketControl->Parammeters.WillTopicName.Length) % 256;

		u16PacketControlIndex += String_Copy(
				&PacketControl_Arr[u16PacketControlIndex],
				PacketControl->Parammeters.WillTopicName.Ptr);

		PacketControl_Arr[u16PacketControlIndex++] =
				(PacketControl->Parammeters.WillMessage.Length) / 256;
		PacketControl_Arr[u16PacketControlIndex++] =
				(PacketControl->Parammeters.WillMessage.Length) % 256;

		u16PacketControlIndex += String_Copy(
				&PacketControl_Arr[u16PacketControlIndex],
				PacketControl->Parammeters.WillMessage.Ptr);
	}

	if (((PacketControl->ConnectFlags.Bit.UserNameFlag) != 0)) {

		PacketControl_Arr[u16PacketControlIndex++] =
				(PacketControl->Parammeters.Username.Length) / 256;
		PacketControl_Arr[u16PacketControlIndex++] =
				(PacketControl->Parammeters.Username.Length) % 256;

		u16PacketControlIndex += String_Copy(
				&PacketControl_Arr[u16PacketControlIndex],
				PacketControl->Parammeters.Username.Ptr);
	}

	if (((PacketControl->ConnectFlags.Bit.PasswordFlag) != 0)) {

		PacketControl_Arr[u16PacketControlIndex++] =
				(PacketControl->Parammeters.Password.Length) / 256;
		PacketControl_Arr[u16PacketControlIndex++] =
				(PacketControl->Parammeters.Password.Length) % 256;

		u16PacketControlIndex += String_Copy(
				&PacketControl_Arr[u16PacketControlIndex],
				PacketControl->Parammeters.Password.Ptr);
	}

	return u16PacketControlIndex;
}

