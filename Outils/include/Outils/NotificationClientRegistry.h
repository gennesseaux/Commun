/*
	from : http://juanchopanzacpp.wordpress.com/2013/02/24/simple-observer-pattern-implementation-c11/
*/

#pragma once


namespace Outils {

	/*
	//		Classe permettant d'enregistrer (abonner) un client pour un �v�nement pr�cis
	//		afin de le notifier d�s que le message est �mis.
	*/
	template <typename Event>
	class NotificationClientEventRegistry
	{
	public:
		// Enregistrement du client pour un �v�nement
		template <typename NotificationClient>
		void registerClient(const Event& event, NotificationClient&& client)
		{
			_clients[event].push_back(std::forward<NotificationClient>(client));
		}

		// Enregistrement du client pour un �v�nement
		template <typename NotificationClient>
		void registerClient(Event&& event, NotificationClient&& client)
		{
			_clients[std::move(event)].push_back(std::forward<NotificationClient>(client));
		}

		// Notification au client de l'�mission de l'�v�nement
		void notifyClient(const Event& event) const
		{
			auto it = _clients.find(event);
			if (it == _clients.end()) return;

			for (const auto& client : _clients.at(event)) client();
		}

		// Suppression du client en fonction d'un �v�nement
		void removeClient(const Event& event)
		{
			auto it = _clients.find(event);
			if (it == _clients.end()) return;
			_clients.erase(it);
		}

		// Nombre de client enregistr� pour un �v�nement
		size_t getClientCount(const Event& event) const
		{
			auto it = _clients.find(event);
			if (it == _clients.end()) return 0;
			else return it->second.size();
		}

	private:
		std::map<Event, std::vector<std::function<void()>>> _clients;
	};




	/*
	//		Cette classe se base sur la classe NotificationClientEventRegistry
	//		mais n'utilise aucun �v�nement.
	*/
	namespace { enum class NoEvent { NoEvent }; }
	class NotificationClientRegistry : public NotificationClientEventRegistry<NoEvent>
	{
	public:
		// Enregistrement du client pour un �v�nement
		template <typename NotificationClient>
		void registerClient(NotificationClient&& client)
		{
			__super::registerClient(NoEvent::NoEvent, client);
		}

		// Notification au client de l'�mission de l'�v�nement
		void notifyClient() const
		{
			__super::notifyClient(NoEvent::NoEvent);
		}

		// Suppression du client en fonction d'un �v�nement
		void removeClient()
		{
			__super::removeClient(NoEvent::NoEvent);
		}

		// Nombre de client enregistr� pour un �v�nement
		size_t getClientCount() const
		{
			return __super::getClientCount(NoEvent::NoEvent);
		}
	};
}

