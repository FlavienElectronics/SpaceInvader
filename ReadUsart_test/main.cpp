#include <iostream>
#include <boost/asio.hpp>
#include <string>

using namespace boost::asio;
using namespace std;

void readUART(serial_port* serial, const string& port, unsigned int baud_rate) {


    char c = 0;
    string data;

    while (c != '\n') {
        read(*serial, buffer(&c, 1)); // Lire un caractère
        if (c == '\n') {            // Fin de ligne -> traiter les données
            std::cout << "Reçu : " << data << std::endl;
            data.clear();           // Réinitialiser le buffer pour les données suivantes
        } else {
            data += c;              // Ajouter le caractère au buffer
        }
    }
}

serial_port* serialConfig(const string& port, unsigned int baud_rate)
{
	io_service io;
	serial_port* serial;
    serial = new serial_port(io, port);

    // Configurer le port série
    serial->set_option(serial_port_base::baud_rate(baud_rate));
    serial->set_option(serial_port_base::character_size(8));
    serial->set_option(serial_port_base::parity(serial_port_base::parity::none));
    serial->set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
	
	return (serial);
}


int main() {
	const string portName = "/dev/ttyUSB0";
	const unsigned int baud_rate = 921600;
	serial_port* mySerial;

try {
		mySerial = serialConfig(portName, baud_rate);

        // Données à envoyer
        //std::string message = "Data from PC!\n";
        //boost::asio::write(serial, boost::asio::buffer(message));

        //std::cout << "Message envoyé : " << message << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
	while(42)
	{
		readUART(mySerial, portName , baud_rate);
	}
	
    return 0;
}
