#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
#include <glm/glm.hpp>

namespace Engine
{

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		void setMouseCoords(float x, float y);

		//True if key is held down
		bool isKeyDown(unsigned int keyID);

		//True if key was just pressed
		bool isKeyPressed(unsigned int keyID);

		//Getters
		glm::vec2 getMouseCoords() const { return m_mouseCoords; }

	private:
		bool wasKeyDown(unsigned int keyID);

		std::unordered_map<unsigned int, bool> m_keyMap;
		std::unordered_map<unsigned int, bool> m_previousKeyMap;

		glm::vec2 m_mouseCoords;
	};

}
#endif //INPUTMANAGER_H