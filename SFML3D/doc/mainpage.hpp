////////////////////////////////////////////////////////////
/// \mainpage
///
/// \section welcome Welcome
/// Welcome to the official SFML3D documentation. Here you will find a detailed
/// view of all the SFML3D <a href="./annotated.php">classes</a> and functions. <br/>
/// If you are looking for tutorials, you can visit the official website
/// at <a href="http://www.sfml3d-dev.org/">www.sfml3d-dev.org</a>.
///
/// \section example Short example
/// Here is a short example, to show you how simple it is to use SFML3D :
///
/// \code
///
/// #include <SFML3D/Audio.hpp>
/// #include <SFML3D/Graphics.hpp>
/// 
/// int main()
/// {
///     // Create the main window
///     sf3d::RenderWindow window(sf3d::VideoMode(800, 600), "SFML3D window");
/// 
///     // Load a sprite to display
///     sf3d::Texture texture;
///     if (!texture.loadFromFile("cute_image.jpg"))
///         return EXIT_FAILURE;
///     sf3d::Sprite sprite(texture);
/// 
///     // Create a graphical text to display
///     sf3d::Font font;
///     if (!font.loadFromFile("arial.ttf"))
///         return EXIT_FAILURE;
///     sf3d::Text text("Hello SFML3D", font, 50);
/// 
///     // Load a music to play
///     sf3d::Music music;
///     if (!music.openFromFile("nice_music.ogg"))
///         return EXIT_FAILURE;
///
///     // Play the music
///     music.play();
/// 
///     // Start the game loop
///     while (window.isOpen())
///     {
///         // Process events
///         sf3d::Event event;
///         while (window.pollEvent(event))
///         {
///             // Close window : exit
///             if (event.type == sf3d::Event::Closed)
///                 window.close();
///         }
/// 
///         // Clear screen
///         window.clear();
/// 
///         // Draw the sprite
///         window.draw(sprite);
/// 
///         // Draw the string
///         window.draw(text);
/// 
///         // Update the window
///         window.display();
///     }
/// 
///     return EXIT_SUCCESS;
/// }
/// \endcode
////////////////////////////////////////////////////////////
