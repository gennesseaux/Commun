/*
	from : http://juanchopanzacpp.wordpress.com/2013/02/24/simple-observer-pattern-implementation-c11/
*/

#pragma once


namespace Outils {

	/*
	//		Classe permettant d'enregistrer (abonner) un client pour un évènement précis
	//		afin de le notifier dès que le message est émis.
	*/
	template <typename Event>
	class NotificationClientEventRegistry
	{
	public:
		// Enregistrement du client pour un évènement
		template <typename NotificationClient>
		void registerClient(const Event& event, NotificationClient&& client)
		{
			_clients[event].push_back(std::forward<NotificationClient>(client));
		}

		// Enregistrement du client pour un évènement
		template <typename NotificationClient>
		void registerClient(Event&& event, NotificationClient&& client)
		{
			_clients[std::move(event)].push_back(std::forward<NotificationClient>(client));
		}

		// Notification au client de l'émission de l'évènement
		void notifyClient(const Event& event) const
		{
			auto it = _clients.find(event);
			if (it == _clients.end()) return;

			for (const auto& client : _clients.at(event)) client();
		}

		// Suppression du client en fonction d'un évènement
		void removeClient(const Event& event)
		{
			auto it = _clients.find(event);
			if (it == _clients.end()) return;
			_clients.erase(it);
		}

		// Nombre de client enregistré pour un évènement
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
	//		mais n'utilise aucun évènement.
	*/
	namespace { enum class NoEvent { NoEvent }; }
	class NotificationClientRegistry : public NotificationClientEventRegistry<NoEvent>
	{
	public:
		// Enregistrement du client pour un évènement
		template <typename NotificationClient>
		void registerClient(NotificationClient&& client)
		{
			__super::registerClient(NoEvent::NoEvent, client);
		}

		// Notification au client de l'émission de l'évènement
		void notifyClient() const
		{
			__super::notifyClient(NoEvent::NoEvent);
		}

		// Suppression du client en fonction d'un évènement
		void removeClient()
		{
			__super::removeClient(NoEvent::NoEvent);
		}

		// Nombre de client enregistré pour un évènement
		size_t getClientCount() const
		{
			return __super::getClientCount(NoEvent::NoEvent);
		}
	};
}

