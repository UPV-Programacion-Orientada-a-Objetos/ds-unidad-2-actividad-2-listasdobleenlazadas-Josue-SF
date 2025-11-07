#include "TramaLoad.h"
#include "TramaMap.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

#include <fcntl.h>   
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <iostream>


int abrir_puerto(const char* puerto) {
    int fd = open(puerto, O_RDWR | O_NOCTTY | O_SYNC);

    if (fd < 0) {

        std::cerr << "Error al abrir el puerto " << puerto << ". Asegúrese de permisos (ej. sudo chmod 666 /dev/ttyUSB0)\n";
        return -1;
    }

    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        std::cerr << "Error al obtener atributos del puerto.\n";
        close(fd);
        return -1;
    }

    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;

    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Modo no canónico
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 5; 

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        std::cerr << "Error al configurar atributos del puerto.\n";
        close(fd);
        return -1;
    }

    std::cout << "Conexión establecida con " << puerto << " (9600 Baud).\n";
    return fd;
}


TramaBase* parsear_linea(char* linea) {
    char* token_tipo = std::strtok(linea, ",");
    if (token_tipo == nullptr) return nullptr;

    char tipo = token_tipo[0];

    char* token_valor = std::strtok(nullptr, ",");
    if (token_valor == nullptr) return nullptr;

    if (tipo == 'L') {
        return new TramaLoad(token_valor[0]);
    } else if (tipo == 'M') {
        int pasos = std::atoi(token_valor);
        return new TramaMap(pasos);
    }

    return nullptr;
}


int main(int argc, char* argv[]) {
    std::cout << "Iniciando Decodificador PRT-7.\n";

    RotorDeMapeo miRotorDeMapeo;

    const char* puerto_serial = "/dev/ttyUSB0";
    int fd = abrir_puerto(puerto_serial);

    if (fd == -1) {
        std::cerr << "Terminando programa debido a error de conexión.\n";
        return 1;
    }
    
    char buffer[256];
    ssize_t n_read;
    TramaBase* trama = nullptr;

    std::cout << "Esperando tramas del Arduino. (Presione Ctrl+C para detener o envíe 'END')\n\n";

    while (true) {

        std::memset(buffer, 0, sizeof(buffer)); // Limpiar buffer
        int i = 0;
        char c;
        
        while (i < 255 && (n_read = read(fd, &c, 1)) > 0) {
            if (c == '\n' || c == '\r') {
                buffer[i] = '\0';
                break;
            }
            buffer[i++] = c;
        }

        if (n_read < 0) {
            std::cerr << "Error de lectura serial o finalización de flujo.\n";
            break;
        }

        if (i > 0) {
            // Simulación de comando de fin (opcional)
            if (std::strcmp(buffer, "END") == 0) {
                std::cout << "\nFlujo de datos terminado por comando END.\n";
                break; 
            }
            
            char linea_copia[256];
            std::strcpy(linea_copia, buffer); 
            std::cout << "Trama recibida: [" << buffer << "] -> ";
            trama = parsear_linea(linea_copia); 
            
            if (trama != nullptr) {

                trama->procesar(&miListaDeCarga, &miRotorDeMapeo);
                
                delete trama;
                trama = nullptr;
            } else {
                std::cerr << "ERROR: Trama mal formada o desconocida.\n";
            }
        }

        usleep(50000);
    }

    std::cout << "\n---\n";
    miListaDeCarga.imprimirMensaje();
    std::cout << "---\n";

    close(fd); // Cierra el puerto serial
    std::cout << "Liberando memoria... Sistema apagado.\n";
    
    return 0;
}
