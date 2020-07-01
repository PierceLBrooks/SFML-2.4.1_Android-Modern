
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML3D/Audio.hpp>
#include <SFML3D/Network.hpp>
#include <iostream>


const sf3d::Uint8 audioData   = 1;
const sf3d::Uint8 endOfStream = 2;


////////////////////////////////////////////////////////////
/// Specialization of audio recorder for sending recorded audio
/// data through the network
////////////////////////////////////////////////////////////
class NetworkRecorder : public sf3d::SoundRecorder
{
public :

    ////////////////////////////////////////////////////////////
    /// Constructor
    ///
    /// \param host Remote host to which send the recording data
    /// \param port Port of the remote host
    ///
    ////////////////////////////////////////////////////////////
    NetworkRecorder(const sf3d::IpAddress& host, unsigned short port) :
    m_host(host),
    m_port(port)
    {
    }

private :

    ////////////////////////////////////////////////////////////
    /// /see SoundRecorder::OnStart
    ///
    ////////////////////////////////////////////////////////////
    virtual bool onStart()
    {
        if (m_socket.connect(m_host, m_port) == sf3d::Socket::Done)
        {
            std::cout << "Connected to server " << m_host << std::endl;
            return true;
        }
        else
        {
            return false;
        }
    }

    ////////////////////////////////////////////////////////////
    /// /see SoundRecorder::ProcessSamples
    ///
    ////////////////////////////////////////////////////////////
    virtual bool onProcessSamples(const sf3d::Int16* samples, std::size_t sampleCount)
    {
        // Pack the audio samples into a network packet
        sf3d::Packet packet;
        packet << audioData;
        packet.append(samples, sampleCount * sizeof(sf3d::Int16));

        // Send the audio packet to the server
        return m_socket.send(packet) == sf3d::Socket::Done;
    }

    ////////////////////////////////////////////////////////////
    /// /see SoundRecorder::OnStop
    ///
    ////////////////////////////////////////////////////////////
    virtual void onStop()
    {
        // Send a "end-of-stream" packet
        sf3d::Packet packet;
        packet << endOfStream;
        m_socket.send(packet);

        // Close the socket
        m_socket.disconnect();
    }

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf3d::IpAddress  m_host;   ///< Address of the remote host
    unsigned short m_port;   ///< Remote port
    sf3d::TcpSocket  m_socket; ///< Socket used to communicate with the server
};


////////////////////////////////////////////////////////////
/// Create a client, connect it to a running server and
/// start sending him audio data
///
////////////////////////////////////////////////////////////
void doClient(unsigned short port)
{
    // Check that the device can capture audio
    if (sf3d::SoundRecorder::isAvailable() == false)
    {
        std::cout << "Sorry, audio capture is not supported by your system" << std::endl;
        return;
    }

    // Ask for server address
    sf3d::IpAddress server;
    do
    {
        std::cout << "Type address or name of the server to connect to : ";
        std::cin  >> server;
    }
    while (server == sf3d::IpAddress::None);

    // Create an instance of our custom recorder
    NetworkRecorder recorder(server, port);

    // Wait for user input...
    std::cin.ignore(10000, '\n');
    std::cout << "Press enter to start recording audio";
    std::cin.ignore(10000, '\n');

    // Start capturing audio data
    recorder.start(44100);
    std::cout << "Recording... press enter to stop";
    std::cin.ignore(10000, '\n');
    recorder.stop();
}
