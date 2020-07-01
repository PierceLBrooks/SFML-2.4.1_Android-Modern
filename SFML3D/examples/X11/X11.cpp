
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML3D/Window.hpp>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>


////////////////////////////////////////////////////////////
/// Initialize OpenGL states into the specified view
///
/// \param Window Target window to initialize
///
////////////////////////////////////////////////////////////
void initialize(sf3d::Window& window)
{
    // Activate the window
    window.setActive();

    // Setup OpenGL states
    // Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.f, 0.5f, 0.5f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 500.f);
}

////////////////////////////////////////////////////////////
/// Draw the OpenGL scene (a rotating cube) into
/// the specified view
///
/// \param window      Target window for rendering
/// \param elapsedTime Time elapsed since the last draw
///
////////////////////////////////////////////////////////////
void draw(sf3d::Window& window, float elapsedTime)
{
    // Activate the window
    window.setActive();

    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Apply some transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.f, 0.f, -200.f);
    glRotatef(elapsedTime * 0.05f, 1.f, 0.f, 0.f);
    glRotatef(elapsedTime * 0.03f, 0.f, 1.f, 0.f);
    glRotatef(elapsedTime * 0.09f, 0.f, 0.f, 1.f);

    // Draw a cube
    glBegin(GL_QUADS);

        glColor3f(1.f, 1.f, 0.f);
        glVertex3f(-50.f, -50.f, -50.f);
        glVertex3f(-50.f,  50.f, -50.f);
        glVertex3f( 50.f,  50.f, -50.f);
        glVertex3f( 50.f, -50.f, -50.f);

        glColor3f(1.f, 1.f, 0.f);
        glVertex3f(-50.f, -50.f, 50.f);
        glVertex3f(-50.f,  50.f, 50.f);
        glVertex3f( 50.f,  50.f, 50.f);
        glVertex3f( 50.f, -50.f, 50.f);

        glColor3f(0.f, 1.f, 1.f);
        glVertex3f(-50.f, -50.f, -50.f);
        glVertex3f(-50.f,  50.f, -50.f);
        glVertex3f(-50.f,  50.f,  50.f);
        glVertex3f(-50.f, -50.f,  50.f);

        glColor3f(0.f, 1.f, 1.f);
        glVertex3f(50.f, -50.f, -50.f);
        glVertex3f(50.f,  50.f, -50.f);
        glVertex3f(50.f,  50.f,  50.f);
        glVertex3f(50.f, -50.f,  50.f);

        glColor3f(1.f, 0.f, 1.f);
        glVertex3f(-50.f, -50.f,  50.f);
        glVertex3f(-50.f, -50.f, -50.f);
        glVertex3f( 50.f, -50.f, -50.f);
        glVertex3f( 50.f, -50.f,  50.f);

        glColor3f(1.f, 0.f, 1.f);
        glVertex3f(-50.f, 50.f,  50.f);
        glVertex3f(-50.f, 50.f, -50.f);
        glVertex3f( 50.f, 50.f, -50.f);
        glVertex3f( 50.f, 50.f,  50.f);

    glEnd();
}


////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Error code
///
////////////////////////////////////////////////////////////
int main()
{
    // Open a connection with the X server
    Display* display = XOpenDisplay(NULL);
    if (!display)
        return EXIT_FAILURE;

    // Get the default screen
    int screen = DefaultScreen(display);

    // Let's create the main window
    XSetWindowAttributes attributes;
    attributes.background_pixel = BlackPixel(display, screen);
    attributes.event_mask       = KeyPressMask;
    Window window = XCreateWindow(display, RootWindow(display, screen),
                               0, 0, 650, 330, 0,
                               DefaultDepth(display, screen),
                               InputOutput,
                               DefaultVisual(display, screen),
                               CWBackPixel | CWEventMask, &attributes);
    if (!window)
        return EXIT_FAILURE;

    // Set the window's name
    XStoreName(display, window , "SFML3D Window");

    // Let's create the windows which will serve as containers for our SFML3D views
    Window view1 = XCreateWindow(display, window,
                                 10, 10, 310, 310, 0,
                                 DefaultDepth(display, screen),
                                 InputOutput,
                                 DefaultVisual(display, screen),
                                 0, NULL);
    Window view2 = XCreateWindow(display, window,
                                 330, 10, 310, 310, 0,
                                 DefaultDepth(display, screen),
                                 InputOutput,
                                 DefaultVisual(display, screen),
                                 0, NULL);

    // Show our windows
    XMapWindow(display, window);
    XFlush(display);

    // Create our SFML3D views
    sf3d::Window SFML3DView1(view1);
    sf3d::Window SFML3DView2(view2);

    // Create a clock for measuring elapsed time
    sf3d::Clock clock;

    // Initialize our views
    initialize(SFML3DView1);
    initialize(SFML3DView2);

    // Start the event loop
    bool running = true;
    while (running)
    {
        while (XPending(display))
        {
            // Get the next pending event
            XEvent event;
            XNextEvent(display, &event);

            // Process it
            switch (event.type)
            {
                // Any key is pressed : quit
                case KeyPress :
                    running = false;
                    break;
            }
        }

        // Draw something into our views
        draw(SFML3DView1, clock.getElapsedTime().asSeconds());
        draw(SFML3DView2, clock.getElapsedTime().asSeconds() * 0.3f);

        // Display the views on screen
        SFML3DView1.display();
        SFML3DView2.display();
    }

    // Close the display
    XCloseDisplay(display);

    return EXIT_SUCCESS;
}
