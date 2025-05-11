#include "ServerLayer.h"

#include "Walnut/Core/Log.h"
#include <Walnut/Serialization/BufferStream.h>
#include <ServerPacket.h>

namespace Cubed
{
	static Walnut::Buffer s_ScratchBuffer;

	void ServerLayer::OnAttach()
	{
		s_ScratchBuffer.Allocate(10 * 1024 * 1024);

		m_Console.SetMessageSendCallback([this](std::string_view message) { OnConsoleMessage(message); });

		m_Server.SetClientConnectedCallback([this](const Walnut::ClientInfo& clientInfo) { OnClientConnected(clientInfo); });
		m_Server.SetClientDisconnectedCallback([this](const Walnut::ClientInfo& clientInfo) { OnClientDisconnected(clientInfo); });
		m_Server.SetDataReceivedCallback([this](const Walnut::ClientInfo& clientInfo, const Walnut::Buffer buffer) { OnDataReceived(clientInfo, buffer); });

		m_Server.Start();
	}

	void ServerLayer::OnDetach()
	{
		m_Server.Stop();
	}

	void ServerLayer::OnUpdate(float ts)
	{
		Walnut::BufferStreamWriter stream(s_ScratchBuffer);
		stream.WriteRaw(PacketType::ClientUpdate);
		m_PlayerDataMutex.lock();
		{
			stream.WriteMap(m_PlayerData);
		}
		m_PlayerDataMutex.unlock();

		m_Server.SendBufferToAllClients(stream.GetBuffer());

		using namespace std::chrono_literals;
		std::this_thread::sleep_for(5ms);
	}

	void ServerLayer::OnUIRender()
	{

	}

	void ServerLayer::OnConsoleMessage(std::string_view message)
	{
		if (message.starts_with('/'))
		{
			//command

			std::cout << "You called the " << message << " command!\n";
		}
	}

	void ServerLayer::OnClientConnected(const Walnut::ClientInfo& clientInfo)
	{
		WL_INFO_TAG("SERVER", "Client connected! ID={}", clientInfo.ID);

		Walnut::BufferStreamWriter stream(s_ScratchBuffer);

		//packet type - connected
		stream.WriteRaw(PacketType::ClientConnect);

		//id
		stream.WriteRaw(clientInfo.ID);

		m_Server.SendBufferToClient(clientInfo.ID, stream.GetBuffer());
	}

	void ServerLayer::OnClientDisconnected(const Walnut::ClientInfo& clientInfo)
	{
		WL_INFO_TAG("SERVER", "Client disconnected! ID={}", clientInfo.ID);
	}

	void ServerLayer::OnDataReceived(const Walnut::ClientInfo& clientInfo, const Walnut::Buffer buffer)
	{
		Walnut::BufferStreamReader stream(buffer);

		PacketType type;
		stream.ReadRaw(type);

		switch (type)
		{
		case PacketType::None:
			break;
		case PacketType::Message:
			break;
		case PacketType::ClientConnectionRequest:
			break;
		case PacketType::ConnectionStatus:
			break;
		case PacketType::ClientList:
			break;
		case PacketType::ClientConnect:
			break;
		case PacketType::ClientUpdate:
			m_PlayerDataMutex.lock();
			{
				PlayerData& playerData = m_PlayerData[clientInfo.ID];
				glm::vec2 pos, vel;
				stream.ReadRaw<glm::vec2>(playerData.Position);
				stream.ReadRaw<glm::vec2>(playerData.Velocity);
			}
			m_PlayerDataMutex.unlock();
			break;
		case PacketType::ClientDisconnect:
			break;
		case PacketType::ClientUpdateResponse:
			break;
		case PacketType::MessageHistory:
			break;
		case PacketType::ServerShutdown:
			break;
		case PacketType::ClientKick:
			break;
		default:
			break;
		}
	}

}