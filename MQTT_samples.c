/****************************************************
 * @file MQTT_samples.c                      	 	*
 * @brief Samples to show how to use this library	*
 * Copyright (c) 2020 E-Vision Corp.        		*
 * Created     : 21/08/2020 10:22:38        	 	*
 * Contributors: Ahmed_Gad 		*
 * Version     : v_01                        		*
 * Edit By     :                             		*
 * Edit Reason :                             		*
 * **************************************************/

	#ifdef TEST_MQTT_SAMPLE1_QOS0
	
				char buf[512];
				char payload[]="Hey i am  Ahmed Gad From E-vision";
				int offeset=0;

				MQTT_ConnectPacketControl_s ConnPacket= MQTT_CONNECT_PACKET__INITIALIZER ;
				MQTT_PublishPacketControl_s PubPacket= MQTT_PUBLISH_PACKET__INITIALIZER;

				ConnPacket.keepAliveInterval=120;
				ConnPacket.ConnectFlags.Bit.CleanSession=1;
				ConnPacket.Parammeters.ClintID.Ptr="EV1";
				//ConnPacket.ConnectFlags.Bit.UserNameFlag=1;
				//ConnPacket.Parammeters.Username.Ptr="a9cBmoeDHSTyRCfnkRDm";
				PubPacket.TopicName.Ptr="developers/Name/Gad";


				offeset = MQTT_Connect(buf, &ConnPacket);
				offeset += MQTT_Publish(buf+offeset, &PubPacket, payload , sizeof(payload)-1);

				/* add your code to send the buf and the length of bytes to send over TCP connection
				 * Example:
				 * now you send a connection request packet then send a puplish packet
				 * TCP_SEND_DATA(buf, offeset);
				 */


				/* to send the connection packet first only do that */

				/* offeset=MQTT_Connect(buf, &ConnPacket); 
				 * TCP_SEND_DATA(buf, offeset);
				 */

				 /* wait for connection request to be accepted then send the publish packet */

				 /* offeset = MQTT_Publish(buf+offeset, &PubPacket, payload , sizeof(payload)-1);
				  * TCP_SEND_DATA(buf, offeset);
				  */



	#endif



