#pragma once

#include <hash_map>
#include <functional>
#include <thread>
#include <mutex>

///
/// Minigui namespace
///
namespace minigui
{
	///
	/// Events namespace
	///
	namespace events
	{
		///
		/// Event class
		///
		template<typename ...Params>
		class event;

		///
		/// Connectio id
		///
		typedef size_t connection_id;

		///
		/// Connection
		///
		template<typename ...Params>
		class connection
		{
			friend class event <Params...>;

		private:
			///
			/// Connection id
			///
			connection_id _id;

			///
			/// Event instance
			///
			event<Params...>& _event;

		protected:
			///
			/// Constructor
			///
			connection(event<Params...>& event, connection_id id)
				: _id(id), _event(event)
			{
			}

		public:
			///
			/// Copy constructor
			///
			connection(const connection& other)
				: _id(other._id)
			{
			}

			///
			/// Connection id
			///
			connection_id id() const
			{
				return this->_id;
			}

			///
			/// Connection is valid
			///
			bool valid() const
			{
				return this->_id != 0;
			}

			///
			/// Enables the event
			///
			void enable()
			{
				if (this->valid())
				{
					this->_event.enable(this->_id);
				}
			}

			///
			/// Enables the event
			///
			void disable()
			{
				if (this->valid())
				{
					this->_event.disable(this->_id);
				}
			}

			///
			/// Assignment operator
			///
			connection& operator=(const connection& other)
			{
				this->_id = other._id;
			}

			///
			/// Comparison operator
			///
			bool operator==(const connection& other) const
			{
				return other._id == this->_id;
			}

			///
			/// Hash function
			///
			size_t hash() const
			{
				return this->_id;
			}
		};

		///
		/// Handler class
		///
		template<typename ...Params>
		class handler
		{
			friend class event < Params... > ;

		public:
			///
			/// Prototype
			///
			typedef std::function<void(Params...)> prototype;

		private:
			///
			/// Enabled
			///
			bool _enabled;

			///
			/// Callback
			///
			prototype _callback;

		protected:
			///
			/// Constructor
			///
			handler(prototype callback)
				: _callback(callback)
			{
			}

			///
			/// Execute the handler
			///
			void execute(Params... params)
			{
				if (this->_callback && this->_enabled)
				{
					this->_callback(params...);
				}
			}

		public:
			///
			/// Enables the handler
			///
			void enable()
			{
				this->_enabled = true;
			}

			///
			/// Disables the handler
			///
			void disable()
			{
				this->_enabled = false;
			}
		};

		///
		/// Event class
		///
		template<typename ...Params>
		class event
		{
			friend class connection<Params...>;
			friend class handler<Params...>;
			
		public:
			///
			/// Prototype
			///
			typedef std::function<void(Params...)> prototype;

		private:
			///
			/// Connection ids
			///
			connection_id _ids;

			///
			/// Slot callbacks
			///
			std::hash_map<connection_id, handler<Params...>*> _handlers;

			///
			/// Mutex
			///
			std::recursive_mutex _mutex;

		protected:
			///
			/// Disables the handler
			///
			void disable(connection_id id)
			{
				std::lock_guard<std::recursive_mutex> locker(this->_mutex);
				auto it = this->_handlers.find(id);
				if (it != this->_handlers.end())
				{
					it->second->disable();
				}
			}

			///
			/// Disables the handler
			///
			void enable(connection_id id)
			{
				std::lock_guard<std::recursive_mutex> locker(this->_mutex);
				auto it = this->_handlers.find(id);
				if (it != this->_handlers.end())
				{
					it->second->enable();
				}
			}

		public:
			///
			/// Constructor
			///
			event() 
			{ 
				this->_ids = 0;
			}

			///
			/// Destructor
			///
			~event() 
			{
				std::lock_guard<std::recursive_mutex> locker(this->_mutex);
				for (auto it = this->_handlers.begin(); it != this->_handlers.end(); ++it)
				{
					delete it->second;
					it = this->_handlers.erase(it);
				}
				this->_handlers.clear();
			}

			///
			/// No copy constructors
			///
			event(const event&) = delete;

			///
			/// No assignment operator
			///
			event& operator=(const event&) = delete;

			///
			/// Register operator
			///
			connection<Params...> operator += (prototype callback)
			{
				std::lock_guard<std::recursive_mutex> locker(this->_mutex);
				while (true)
				{
					auto id = ++this->_ids;
					if (id == 0) 
					{
						continue;
					}

					if (this->_handlers.find(id) == this->_handlers.end()) 
					{
						this->_handlers[id] = new handler<Params...>(callback);
						return connection<Params...>(*this, id);
					}
				}

				return connection<Params...>(*this, 0);
			}

			///
			/// Register operator
			///
			void operator -= (const connection<Params...>& conn)
			{
				std::lock_guard<std::recursive_mutex> locker(this->_mutex);
				auto it = this->_handlers.find(conn.id());
				if (it != this->_handlers.end())
				{
					delete it->second;
					this->_handlers.erase(it);
				}
			}

			///
			/// Calls the handlers
			///
			void operator() (Params... params)
			{
				std::lock_guard<std::recursive_mutex> locker(this->_mutex);
				for (auto it = this->_handlers.begin(); it != this->_handlers.end(); ++it)
				{
					it->second->execute(params...);
				}
			}
		};
	}
}