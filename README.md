# SNESPico

A Super Nintendo(SNES) emulator in Rasberry PI Pico

[Reference](https://wiki.superfamicom.org/65816-reference)


Equipe:
| [<img src="https://avatars.githubusercontent.com/u/96800329?v=4" width=115><br><sub>Luiz Gustavo</sub>](https://github.com/Zed201) |  [<img src="https://avatars.githubusercontent.com/u/123107373?v=4" width=115><br><sub>Márcio Campos</sub>](https://github.com/MAACJR032)  | [<img src="https://avatars.githubusercontent.com/u/98539736?v=4" width=115><br><sub>João Victor</sub>](https://github.com/jambis-prg) |
| :---: | :---: | :--:|


### Setup
#### Dependências
Basicamente tem que ter o cmake, git, python3, build-essential(ou build-devel no aur), gcc-arm-none-eabi, libnewlib-arm-none-eabi e libstdc++-arm-none-eabi-newlib
```
sudo apt install cmake git python3 build-essential gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
```

```
sudo pacman -Sy cmake git python3 base-devel arm-none-eabi-newlib arm-none-eabi-gcc
```

#### Comandos de build
Depois de clonar tudo do github, com submodule recursive, coloca no terminal `. setup.sh` para ele executar a importação de algumas coisas e dar build no projeto, o arquivo `*.elf` ele é para ser testado com debugger e o `*.uf2` é para ser instalado no Rasberry Pi Pico

### Extras
- Uso do serial: Para poder usar o serial como um console no computador é necessário instalar o programa puTTY para que ele possa simular o terminal para o raspberry pi pico. O programa deve seguir as seguintes configurações
  
  ![image](https://github.com/user-attachments/assets/5274ac69-c26f-44b3-91ff-340a5a579c71)

  Para descobrir o número da porta basta apenas abrir o **Gerenciador de Dispositivos** e abrir a aba **Portas (COM e LPT)**
  
  ![image](https://github.com/user-attachments/assets/e9a5f109-c928-4c38-81aa-dc4bbd121f77)

  No arquivo CMakeLists.txt é necessário adicionar as seguintes linhas de código
  ```
  pico_enable_stdio_usb({nome do executavel} 1)
  pico_enable_stdio_uart({nome do executavel} 0)
  ```
  Caso você também queira usar a saída serial pela interface UART então defina a última linha para 1 em vez de 0

