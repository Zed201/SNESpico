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
