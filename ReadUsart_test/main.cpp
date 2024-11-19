#include <iostream>
#include <boost/asio.hpp>
#include <string>

using namespace boost::asio;
using namespace std;

void readUART(const string& port, unsigned int baud_rate) {
    io_service io;
    serial_port serial(io, port);

    // Configurer le port série
    serial.set_option(serial_port_base::baud_rate(baud_rate));
    serial.set_option(serial_port_base::character_size(8));
    serial.set_option(serial_port_base::parity(serial_port_base::parity::none));
    serial.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));

    char c;
    std::string data;

    while (true) {
        read(serial, buffer(&c, 1)); // Lire un caractère
        if (c == '\n') {            // Fin de ligne -> traiter les données
            std::cout << "Reçu : " << data << std::endl;
            data.clear();           // Réinitialiser le buffer pour les données suivantes
        } else {
            data += c;              // Ajouter le caractère au buffer
        }
    }
}


int main() {
	const string portName = "/dev/ttyUSB0";
	const unsigned int baud_rate = 9600;

    try {
        boost::asio::io_service io_service;
        boost::asio::serial_port serial(io_service, portName); // Remplacez par le bon port
        serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
        
        std::cout << "Serial port opened successfully!" << std::endl;
    } catch (const boost::system::system_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
	
	readUART(portName , baud_rate);
	
	
    return 0;
}
