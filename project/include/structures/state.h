/**
 * State.h
 *
 *	Interfaz que debe implementar cualquier estado
 *	de la maquina de estados.
 *
 *  Created on: 06/04/2011
 *      Author: jorge
 */

#ifndef STATE_H_
#define STATE_H_

namespace dc
{
	/**
	 * Interfaz que debe implementar cualquier estado
	 * de la maquina de estados.
	 */
	class CState
	{
	public:
		static const int INVALID_ID = -1;

	public:

		const int Id() const
		{
			return m_identifier;
		}
		CState* Parent() const
		{
			return mp_parentState;
		}

	public:

		CState(const int identifier) :
				m_identifier(identifier), mp_parentState(0)
		{
		}

		CState(const CState& copy) = delete;
		/**
		 * Destructor
		 */
		virtual ~CState()
		{
		}

		// Life cycle methods
	public:
		/**
		 * Función llamada cuando se crea el estado.
		 * Sirve para inicializar todos aquellos elementos
		 * que solo necesitan iniciarse una vez.
		 */
		virtual void OnCreate()
		{
		}

		/**
		 * Función llamada cuando se elimina el
		 * estado de la aplicación.
		 *
		 * Deberian destruirse todos los elementos
		 * inicializados en onCreate
		 */
		virtual void OnDestroy()
		{
		}

		/**
		 * Función llamada por la aplicación cuando se activa
		 * el estado.
		 *
		 * Aqui se inician todos aquellos parametros que tengan
		 * que resetear su valor cada vez que se activa un
		 * estado
		 */
		virtual void OnActivate()
		{
		}

		/**
		 * Función llamada por la aplicación cuando se desactiva
		 * el estado.
		 */
		virtual void OnDeactivate()
		{
		}

		virtual void OnTick()
		{
		}

	protected:
		int m_identifier;
		CState* mp_parentState;

	};
}
#endif /* STATE_H_ */
