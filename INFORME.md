    Comence usando la terminal de ubuntu donde hice clone del repositorio directamente del xv6.
    Despues intente instalar el toolchain siguiendo lo pasos del repositorio sin mucho avance ya que el qemu segui sin isntalarse y me daban error los  ./configure
    esto seguramente debido a que la carpeta donde estaba parado no habia un archivo llamado asi

    Para la version que si me funciono comence de nuevo la instalacion pero ahora en Visual Studio Code.
    Comence haciendole fork al repositorio del profe y no al de MIT
    Despues utilice una pagina para instalar el toolchain
    Instalando dependencias como autoconf automake python3 etc.
    despues cree la carpeta donde estaria el toolchain y lo clone
    agregue al agregue el /opt/riscv al ./configure 
    hice sudo make para que se instalen las ocsas necesarias por alrededor de 2 horas
    agregue por ultimo el /opt/riscv/bin al Path

    esto seguia sin permitirme usar qemu asi que tuve que hacer git clone al qemu-project en gitlab
    y seguir una lista de configuraciones para habilitarlo

    Con eso make qemu ya funciona en xv6-riscv como aparece en el pantallazo.


