#include <stdio.h>
#include "bus.h"

// para testar sem mexer com o rasberry pi por enquanto
// a rom do mario tem 513KiB ou 513Kb -> 513000 bytes mais ou menos
int main(){
    Bus m;
    char * file = "./Mario_rom.smc";
    m.ReadRom(file);
    uint64_t ini = 0x007FC0, end = 0x007FDF; // primeiro cabeçalho Lorom, mario é desse tipo
    // verificar o tipo de room pelos valores do titulo, que devem ser ascii
    // uint64_t ini = 0x00FFC0, end = 0x00FFDF; // primeiro cabeçalho hirom
    // uint64_t ini = 0x40FFC0, end = 0x40FFDF; // primeiro cabeçalho exhirom

    for(uint64_t i = ini; i <= end; i++){
        printf("%x = %c,\n",i,  m.Ram_ReadByte(i));
    }
    // printf("tamanho da rom %d\n tamanho da ram %d", m.Ram_ReadByte(0x15), m.Ram_ReadByte(0x16));
    // printf("%02X", m.Ram_ReadByte(0xFFD5));

    /*
        TODO:
        Estudar como identificar o tipo da rom e com isso mapear onde cada parte esta
    
    */

    return 0;
}