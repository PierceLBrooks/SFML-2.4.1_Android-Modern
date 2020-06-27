#include "native-lib.hpp"

int main(int argc, char *argv[])
{
    // Retrieve the JVM
    JavaVM* vm = getJvm();

    // Retrieve the JNI environment
    JNIEnv* env = getEnv();

    jint res = vm->AttachCurrentThread(&env, NULL);

    if (res == JNI_ERR) {
        LOGGER << "ERROR";
        return EXIT_FAILURE;
    }

    sf::VideoMode screen(sf::VideoMode::getDesktopMode());

    sf::RenderWindow window(screen, "");
    window.setFramerateLimit(30);

    sf::View view = window.getDefaultView();

    sf::Color background = sf::Color::White;

    // We shouldn't try drawing to the screen while in background
    // so we'll have to track that. You can do minor background
    // work, but keep battery life in mind.
    bool active = true;

    while (window.isOpen())
    {
        sf::Event event;

        while (active ? window.pollEvent(event) : window.waitEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
                case sf::Event::Resized:
                    view.setSize(event.size.width, event.size.height);
                    view.setCenter(event.size.width/2, event.size.height/2);
                    window.setView(view);
                    break;
                case sf::Event::LostFocus:
                    background = sf::Color::Black;
                    break;
                case sf::Event::GainedFocus:
                    background = sf::Color::White;
                    break;
                // On Android MouseLeft/MouseEntered are (for now) triggered,
                // whenever the app loses or gains focus.
                case sf::Event::MouseLeft:
                    active = false;
                    break;
                case sf::Event::MouseEntered:
                    active = true;
                    break;
                case sf::Event::TouchBegan:
                    if (event.touch.finger == 0)
                    {
                        vibrate(sf::milliseconds(100));
                    }
                    break;
            }
        }

        if (active) {
            window.clear(background);
            window.display();
        } else {
            sf::sleep(sf::milliseconds(100));
        }
    }

    // Detach thread again
    vm->DetachCurrentThread();

    return EXIT_SUCCESS;
}
