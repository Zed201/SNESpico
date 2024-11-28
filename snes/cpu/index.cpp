#include <stdio.h>
#include "bus.h"

// para testar sem mexer com o rasberry pi por enquanto
int main(){
    Bus m;
    char * file = "./Mario_rom.smc";
    m.ReadRom(file);
    for (size_t i = 0; i < m.rom_Size; i++)
    {
        printf("%X ", m.Ram_ReadByte(i));
        
        if (i % 4 == 0){
            printf(" ");
        }
        if (i % 16 == 0){
            printf("\n");
        }
    }
    printf("\n");

    /*
        TODO:
        Estudar como identificar o tipo da rom e com isso mapear onde cada parte esta
    
    */

    return 0;
}