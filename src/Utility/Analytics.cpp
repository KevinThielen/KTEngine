#include "Utility/Analytics.h"
#include <enet/enet.h>
#include <stdio.h>

bool kte::Analytics::enabled = false;

kte::Analytics::Analytics(std::string host, unsigned int port) : HOST(host), PORT(port)
{
    //load old data
    if(data.read("analytics.file"))
    {
	dataToString();
	//send old data if exists
	sendData();
    }
    else
    {
	//create new file
	data["ID"] = "";
	data.persist("analytics.file");
	sendData();
	
    }
}

std::string kte::Analytics::dataToString()
{
    std::string dataString = "";
    Json::FastWriter fastWriter;
    dataString = fastWriter.write(data.getRoot());    
    std::cout<<dataString<<std::endl;
    return dataString;
}

bool kte::Analytics::sendData()
{
    if(!enabled)
	return true;
    
    ENetHost * client;
    
    if (enet_initialize())   
    {
	std::cout<<"Couldn't initalize Enet"<<std::endl;
        return false;
    }
    
    
    client = enet_host_create (NULL /* create a client host */,
            1 /* only allow 1 outgoing connection */,
            2 /* allow up 2 channels to be used, 0 and 1 */,
            57600 / 8 /* 56K modem with 56 Kbps downstream bandwidth */,
            14400 / 8 /* 56K modem with 14 Kbps upstream bandwidth */);
    if (client == NULL)
    {
	std::cout<<"Couldn't create Enet Host"<<std::endl;
	return false;
    }

    ENetAddress address;
    ENetEvent event;
    ENetPeer* peer;
    ENetPacket* packet;
    
    enet_address_set_host(&address,HOST.c_str());
    address.port = PORT;

    peer = enet_host_connect(client, &address, 2, 0);
    
    if(!peer)
    {
	std::cout<<("Couldnt connect to server")<<std::endl;
	return 0;
    }
    
    bool connected = false;
    
    char buffer[1000];
    
    
    //LOGIN/Request USER ID/send data
    if(enet_host_service(client, &event, 1000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
    {
	std::cout<<("Connected to server")<<std::endl;
	connected = true;
	
	std::string userLogin = "LOGIN ";
	
	if(!data["ID"].empty())
	    userLogin += data["ID"].asString();
	
	
	
	strncpy(buffer, userLogin.c_str(), 1000);
	
	
	packet = enet_packet_create(buffer, strlen(buffer)+1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
    }
    else
    {
	enet_peer_reset(peer);
	printf("No connection");
	return 0;
    }	
    
    while(connected)
    {
	std::string data = "";
	while (enet_host_service(client, &event, 1000) > 0) 
	{
	     switch (event.type) 
	     {
		 case ENET_EVENT_TYPE_RECEIVE:
		 {
		     data = (char*)event.packet->data;
		     std::cout<<"Response: "<<data<<std::endl;
		
		     //if first substr is ID, save new user ID
		     int index = data.find_first_of(" ")+1; 
		
		     if(index > 0 && data.substr(0, index-1) == "LOGIN_ID")
		     {
			 std::cout<<"New ID: "<<data.substr(index)<<std::endl;
			 this->data["ID"] = data.substr(index);
			 this->data.persist("analytics.file");
 

			 std::string updateRequest = "UPDATE "+dataToString();
		
			packet = enet_packet_create(updateRequest.c_str(), strlen(updateRequest.c_str())+1, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(event.peer, 0, packet);
			free(event.peer->data);
		     }
		     else if(index > 0 && data.substr(0, index-1) == "LOGIN_SUCCESS")
		     {
			 std::string updateRequest = "UPDATE "+dataToString();
		
			 std::cout<<"Request :"<<updateRequest<<std::endl;
			packet = enet_packet_create(updateRequest.c_str(), strlen(updateRequest.c_str())+1, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(event.peer, 0, packet);
			free(event.peer->data);
		     }
		     else if(index > 0 && data.substr(0, index-1) == "OK")
		     {
			 //reset the backup file: Data has been sent
			 std::string ID = this->data["ID"].asString();
			 resetData();
			 this->data["ID"] = ID;
			 
			 this->data.persist("analytics.file");
			 
			connected = false;
			enet_peer_disconnect(peer, 0);
		     }		
	             else 
		     {
			  std::cout<<"Response: "<<data.substr(index)<<std::endl;
			connected = false;
			enet_peer_disconnect(peer, 0);
		     }
		     break;
		 }
		 case ENET_EVENT_TYPE_DISCONNECT:
		 {
		     
		     connected = false;
		      std::cout<<("Disconnected")<<std::endl;
		      return true;
		 } 
		 default: break;
	     }
	}
    }
    enet_deinitialize();


    return true;   
}