#include "NetworkManager.h"
#include <thread>

NetworkManager::NetworkManager()
{
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occured while initializing Enet!\n");
		return;
	}
	atexit(enet_deinitialize);

	client = enet_host_create(NULL, 1, 1, 0, 0);

	if (client == NULL)
	{
		fprintf(stderr, "An error occured while trying to create an ENet client host !\n");
		return;
	}

	ENetAddress address;
	ENetEvent event;
	ENetPeer *peer;

	enet_address_set_host(&address, "127.0.0.1");
	address.port = 7777;

	peer = enet_host_connect(client, &address, 1, 0);
	if (peer == NULL)
	{
		fprintf(stderr, "No available peers for initiating an ENet connection\n");
		return;
	}

	if (enet_host_service(client, &event, 5000) > 0 &&
		event.type == ENET_EVENT_TYPE_CONNECT)
	{
		puts("Connection to 127.0.0.1:7777 succeeded.");
	}
	else
	{
		enet_peer_reset(peer);
		puts("Connection to 127.0.0.1:7777 failed.");
		return;
	}

	std::thread(&NetworkManager::GetMessagesFromServerLoop, this).detach();
}

void NetworkManager::ParseData(unsigned char *data)
{
	int data_type;
	int id;
	const char *dataStr = reinterpret_cast<const char *>(data);
	sscanf(dataStr, "%d|%d", &data_type, &id);
	switch (data_type)
	{
	case 3:
		printf("ID: %d", id);
		break;
	}
}

NetworkManager &NetworkManager::GetInstance()
{
	static NetworkManager instance;
	return instance;
}

void NetworkManager::SendRequest(const std::string &type, Callback cb)
{
	// Giả lập: gửi lên server (có thể chạy thread riêng)
	// Sau 2 giây trả kết quả
	std::thread([cb]()
				{
		std::this_thread::sleep_for(std::chrono::seconds(2));
		bool result = true;
		cb(result); })
		.detach();
}

void NetworkManager::GetMessagesFromServerLoop()
{
	while (true)
	{
		ENetEvent event;
		while (enet_host_service(client, &event, 1000) > 0)
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_RECEIVE:
				// printf("A packet of length %u containing %s was received from %s on channel %u.\n",
				// event.packet->dataLength,
				// event.packet->data,
				// event.peer->data,
				// event.channelID);
				ParseData(event.packet->data);
				enet_packet_destroy(event.packet);

				break;
			}
		}
	}
}
