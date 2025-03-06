# Introducción

En este documento, exploraremos la instalación de un software de máquinas virtuales (denominado aquí como **VMSW**), que crea una capa de abstracción sobre el hardware, permitiendo ejecutar varias máquinas virtuales simultáneamente en un mismo servidor. Una alternativa moderna a esta tecnología es el uso de contenedores (como Docker), que comparten recursos entre los contenedores y el anfitrión. En este primer bloque nos centraremos en la **virtualización**, instalando un software como **VirtualBox**, aunque también mencionaremos otra alternativa popular.

### Diferencia entre Hyper-V y VirtualBox

- **Hyper-V**: Es un hipervisor de tipo 1 desarrollado por Microsoft, integrado en Windows. Opera directamente sobre el hardware, ofreciendo mejor rendimiento en entornos Windows y soporte nativo para sistemas Microsoft. Sin embargo, requiere un sistema operativo compatible y no es tan flexible para usuarios de Linux o macOS.
- **VirtualBox**: Es un hipervisor de tipo 2 de Oracle, que se ejecuta sobre un sistema operativo anfitrión. Es gratuito, de código abierto y más versátil, permitiendo una amplia compatibilidad con diferentes sistemas operativos invitados, aunque puede tener un rendimiento ligeramente inferior al depender del anfitrión.

## Realización

### Instalación de VirtualBox
- **Enlace de descarga**: [VirtualBox Downloads](https://www.virtualbox.org/wiki/Downloads)
- **Para Arch Linux**:
 ```
sudo pacman -S virtualbox
```

### Alternativa: VMware
- **Enlace**: [VMware Workstation y Fusion](https://www.vmware.com/products/desktop-hypervisor/workstation-and-fusion)

---

# Instalación de Rocky Linux

Utilizaremos el **VMSW** (por ejemplo, VirtualBox) para instalar **Rocky Linux** en modo mínimo, sin entorno gráfico, incluyendo el demonio **sshd**. La instalación será por defecto, pero crearemos una cuenta no root con privilegios administrativos. La máquina tendrá **dos tarjetas de red**, configuradas teniendo en cuenta:

### Modos de red en VirtualBox
- **Not Attached**: Simula una tarjeta sin conexión, como si no hubiera cable.
- **NAT**: Ideal para navegación y descargas básicas; traduce direcciones de red del invitado al anfitrión.
- **NAT Network**: Permite conexiones salientes en una red interna.
- **Bridged Networking**: Conecta la VM directamente a la red física del anfitrión, útil para servidores o simulaciones.
- **Internal Networking**: Crea una red aislada visible solo para las VMs seleccionadas.
- **Host-Only Networking**: Conecta el anfitrión y las VMs sin acceso externo, usando una interfaz virtual.
- **Cloud Networking**: Conecta la VM a una subred en un servicio en la nube.
- **Generic Networking**: Modos avanzados con control de drivers específicos.

Configuraremos una tarjeta en **NAT** (para acceso a internet) y otra en **Host-Only** con una **IP estática** (para comunicación entre el anfitrión y el invitado). También estableceremos un **hostname** (nombre legible para identificar la máquina).

### Snapshot
Tras la configuración, crearemos un **snapshot** de la VM, que guarda su estado actual (configuración, archivos y memoria si está en ejecución). Esto permite volver al estado inicial en cualquier momento. A diferencia de un **clon** (otra máquina independiente), el snapshot depende de la VM original.

### sshd
El demonio **sshd** gestiona conexiones SSH, proporcionando comunicación segura entre hosts. Se activa al inicio desde `/etc/rc`.

## Realización

1. Descarga Rocky Linux desde su [página oficial](https://rockylinux.org/) o este [enlace directo](http://atcproyectos.ugr.es/esriie/Rocky-9.0-20220805.0-x86_64-minimal.iso). Guarda la ISO en un directorio estable.
2. Arrastra la ISO a VirtualBox para abrir el menú de importación:
 - Deja las opciones por defecto, ajustando nombre y recursos (CPU, RAM) si deseas más rendimiento.
 - Activa **Enable EFI** para evitar errores.
3. Inicia la VM y en el menú de instalación:
 - (1) Crea un usuario no root con contraseña y permisos administrativos.
 - (2) Configura el **hostname** (ejemplo: `dekMV01` para Donald Ervin Knuth).
4. Tras instalar, verifica en la terminal:
 - `systemctl status sshd` (comprueba que sshd esté activo).
 - Confirma que el usuario tiene privilegios de superusuario.
5. Configurar el prompt:
 - (1) Edita el fichero .bashrc
 - (2) Añade una linea para modificar el prompt (por ejemplo): PS1='\[\u@\h \W\] \[\e[0;32m\]\t \W>\[\e[1;37m\]'
 - (3) Aplica los cambios a la sesión actual con source .bashrc
6. Configura las redes en VirtualBox:
 - Adaptador 1: **NAT**.
 - Adaptador 2: **Host-Only Adapter**, con "Cable Connected" activado.
7. Para la ip estática
 - vi /etc/sysconfig/network-scripts/ifcfg-enp0s8
 - Añadir:
 ```
DEVICE=enp0s8
BOOTPRO=none
ONBOOT=yes
IPADDR=192.168.56.12
NETMASK=255.255.255.0
```
7. Guarda y crea un **snapshot** desde el menú de snapshots como estado de referencia.
8. Verifica el funcionamiento:
 - Ping desde el anfitrión a la VM y viceversa.
 - Conéctate por SSH desde el anfitrión.
 - Haz ping a internet desde la VM (ejemplo: `ping 1.1.1.1`).

---

# Configuración de LVM

El **Logical Volume Manager (LVM)** abstrae el almacenamiento físico, permitiendo crear volúmenes lógicos flexibles. Esto elimina restricciones de tamaño físico y separa la configuración hardware del software, facilitando ajustes sin desmontar el sistema de archivos.

### Componentes de LVM
- **Physical Volumes (PV)**: Discos o particiones físicas inicializadas para LVM.
- **Volume Groups (VG)**: Grupos que combinan PVs para formar un pool de almacenamiento.
- **Logical Volumes (LV)**: Volúmenes lógicos creados desde el VG, usados como particiones flexibles.

En este apartado modificaremos la configuración por defecto de Rocky Linux para usar LVM.

## RAID

**RAID** (Redundant Array of Independent/Inexpensive Disks) agrupa dispositivos de almacenamiento en un dispositivo virtual con características específicas. Nos centraremos en tres niveles:

- **RAID 0**: Combina discos con *striping* para mayor velocidad, pero sin redundancia. Usado en HDD, no en SSD (puede ralentizar).
- **RAID 1**: Duplica datos entre discos para redundancia total, sacrificando capacidad.
- **RAID 5**: Requiere 3+ discos, combina velocidad (*striping*) y redundancia con paridad distribuida. Menos recomendado hoy por alternativas modernas.

## Administración del Sistema de Archivos

### systemd
**systemd** es el sistema de inicio predominante en Linux, reemplazando a SysVinit. SysVinit usaba niveles de ejecución (runlevels) con capacidades específicas, mientras que systemd ofrece un enfoque más modular.

### Jerarquía del sistema de archivos
- `/bin`: Binarios de comandos esenciales.
- `/boot`: Archivos estáticos del cargador de arranque.
- `/dev`: Archivos de dispositivos.
- `/etc`: Configuración específica del sistema.
- `/lib`: Bibliotecas compartidas esenciales y módulos del kernel.
- `/media`: Punto de montaje para medios extraíbles.
- `/mnt`: Punto de montaje temporal para sistemas de archivos.
- `/opt`: Paquetes de software adicionales.
- `/sbin`: Binarios esenciales del sistema.
- `/srv`: Datos de servicios del sistema.
- `/tmp`: Archivos temporales.
- `/usr`: Jerarquía secundaria (binarios, bibliotecas, etc.).
- `/var`: Datos variables (logs, bases de datos, etc.).

### Sistemas de archivos
- **ext4**: El más usado, rápido y robusto, con soporte para volúmenes y archivos grandes.
- **btrfs**: Basado en árboles B, usa *copy-on-write* para mayor integridad, pero es más lento.
Para manejar y consultar cómodamente los montajes y discos conectados podemos usar las siguientes herramientas:
- lsblk: Para ver las distintas particiones y discos conectados
- df -h: Disk free, nos da el espacio disponible en disco, -h se usa para el formato humano

### /etc/fstab
Archivo que facilita montar/desmontar sistemas de archivos, su estructura se compone de varias columnas para cada sistema, con las siguientes correspondencias y orden:

- **Device**: Nombre o UUID del dispositivo (ej. `/dev/sda1`).
- **Mount Point**: Directorio donde se monta (ej. `/mnt`).
- **File System Type**: Tipo de sistema (ej. `ext4`).
- **Options**: Opciones de montaje (ej. `defaults`).
- **Backup Operation**: 1 para respaldo (obsoleto), 0 para ninguno.
- **FS Check Order**: 0 (sin chequeo), 1 (raíz), 2 (otros).

## Ejercicio Opcional: Servicio de Gestión Documental

Partiendo de un servidor básico configurado según el apartado 2 (Rocky Linux en VirtualBox con LVM, dos tarjetas de red y sshd), se plantea la instalación de un **servicio de gestión documental**. Este servicio requiere:
- **Espacio de almacenamiento creciente**: Posiblemente considerable con el tiempo.
- **Contenido crítico**: Necesita un mecanismo de respaldo ante fallos de hardware.
- **Máxima disponibilidad**: Garantizando la conservación de datos y continuidad del servicio.


## Diseño del Sistema de Almacenamiento

### Requisitos y Solución Propuesta
1. **Crecimiento del almacenamiento**: Usaremos **LVM** (Logical Volume Manager) para permitir la expansión dinámica del espacio, añadiendo discos según sea necesario sin interrumpir el servicio.
2. **Redundancia ante fallos**: Implementaremos **RAID 1** (mirroring) para duplicar los datos entre dos discos, asegurando que un fallo en uno no comprometa la información. (RAID 5 también sería válido)
3. **Sistema de archivos**: Optaremos por **ext4** por su rendimiento, estabilidad y soporte amplio en Linux, aunque se considerará **btrfs** como alternativa por su capacidad de snapshots y mayor integridad de datos.
4. **Disponibilidad**: La combinación de LVM y RAID 1, junto con copias de seguridad regulares, maximizará el tiempo de actividad y la recuperación ante desastres.

# Acceso Seguro al Servidor

**iptables** es una utilidad de Linux para configurar el firewall a nivel de kernel. En Rocky Linux, usamos **firewalld**, un frontend más sencillo, gestionado mediante el comando `firewall-cmd`. Este se ejecuta como un servicio y podemos activarlo o verificarlo así:
```
sudo systemctl enable --now firewalld
sudo systemctl status firewalld
```

### Comandos básicos de `firewall-cmd`
- `firewall-cmd --state`: Muestra el estado del firewall.
- `firewall-cmd --reload`: Recarga la configuración (necesario tras cambios permanentes).
- `firewall-cmd --list-all`: Lista la configuración actual.
- `firewall-cmd --runtime-to-permanent`: Guarda los cambios temporales como permanentes.

## Zonas

Las **zonas** son conjuntos de reglas que se aplican según el nivel de confianza de la red. Ejemplo: conexiones Ethernet más confiables que Wi-Fi. Resumen de las principales zonas:

- **drop**: Bloquea todo el tráfico entrante sin respuesta; solo permite saliente.
- **block**: Similar a drop, pero rechaza con mensaje ICMP.
- **public**: Para redes públicas no confiables; permite conexiones selectivas.
- **external**: Para redes externas con NAT; oculta la red interna.
- **internal**: Para redes internas de confianza moderada.
- **dmz**: Para equipos aislados en una DMZ.
- **work**: Para redes de trabajo; confianza media.
- **home**: Para entornos domésticos; confianza alta.
- **trusted**: Máxima confianza; todo permitido (usar con precaución).

Normalmente usaremos **trusted**, **home** o **public**. Para ver la zona por defecto:
```
firewall-cmd --get-default-zone
```

### Gestión de zonas
- Cambiar zona por defecto: `firewall-cmd --set-default-zone=[zona]`
- Añadir interfaz a zona: `firewall-cmd --zone=[zona] --add-interface=[dispositivo]`
- Cambiar zona de interfaz: `firewall-cmd --zone=[zona] --change-interface=[dispositivo]`
- Eliminar interfaz de zona: `firewall-cmd --zone=[zona] --remove-interface=[dispositivo]`

## Puertos

Para servicios comunes como **SSH**, **FTP** o **HTTPS**, es mejor gestionarlos como servicios, no como puertos. Comandos útiles:

- `firewall-cmd --list-ports`: Lista puertos abiertos (alternativa: `nmap`).
- `firewall-cmd --zone=public --add-port=[numero]/[tcp/udp]`: Abre un puerto.
- `firewall-cmd --zone=public --remove-port=[numero]/[tcp/udp]`: Cierra un puerto.

### Gestión de servicios
- Lista de servicios disponibles: `firewall-cmd --get-services`
- Servicios activos: `firewall-cmd --list-services`
- Añadir servicio: `firewall-cmd --zone=public --add-service=[servicio]`
- Eliminar servicio: `firewall-cmd --zone=public --remove-service=[servicio]`

## Restricción de Acceso

Para un servidor no público (ej. acceso SSH restringido), hay dos enfoques:

### 1. Zona restrictiva con IP específica
1. Usa una zona como **trusted** y asigna tu interfaz.
2. Añade el servicio SSH: `firewall-cmd --zone=trusted --add-service=ssh`.
3. Restringe acceso a una IP o rango:
```
firewall-cmd --permanent --zone=trusted --add-source=192.168.1.0/24
```
(Cambia `--add-source` por `--remove-source` para revertir).

### 2. Combinación de zonas (público + privado)
Para un servidor con servicios públicos (ej. web) pero SSH restringido:

- **Zona public**: Interfaz asignada, con servicios como HTTP/HTTPS:
```
firewall-cmd --zone=public --add-service=http
firewall-cmd --zone=public --add-service=https
```
- **Zona trusted**: Solo para SSH desde un rango IP:
```
firewall-cmd --zone=trusted --add-source=192.168.1.0/24
firewall-cmd --zone=trusted --add-service=ssh
```
- Elimina SSH de la zona pública:
```
firewall-cmd --zone=public --remove-service=ssh
```

### Nota
Si pierdes acceso, reinicia el servidor desde el panel de control del VPS y ajusta la configuración. Guarda cambios con `--runtime-to-permanent` solo tras probar.

