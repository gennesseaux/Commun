
#pragma once

// Inclusions
#include <mutex>

namespace Outils {

	template <class Singleton>
	class SafeSingletonHolder
	{
	public:
		// Instance du singleton
		static Singleton& getInstance()
		{
			std::call_once(SafeSingletonHolder::_only_one, [](){ SafeSingletonHolder::_instance.reset(new Singleton()); });

			return *SafeSingletonHolder::_instance;
		}

		// Constructeur
		SafeSingletonHolder() = default;
		// Destructeur
		~SafeSingletonHolder() = default;

	private:
		// Constructeur par copie
		SafeSingletonHolder(const SafeSingletonHolder& rs) = delete;
		// opérateur d'assignement
		SafeSingletonHolder& operator = (const SafeSingletonHolder& rs) = delete;

	private:
		static std::shared_ptr<Singleton>	_instance;
		static std::once_flag				_only_one;
	};

	template <class Singleton> std::shared_ptr<Singleton> SafeSingletonHolder<Singleton>::_instance = nullptr;
	template <class Singleton> std::once_flag Outils::SafeSingletonHolder<Singleton>::_only_one;
}
