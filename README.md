ok so making my own bootloader, while fun and interesting, is NOT the way to go for this project. so from now on, im just going to use a bootloader someone else wrote, specifically [Limine](https://github.com/Limine-Bootloader/Limine).

# goals

ok so goals for this project: 
  - Lightweight and portable (small size)
  - Compatibility (performant and not reliant on too many cutting-edge CPU features, able to run on older machines)
  - that one core chroot feature (will describe better later)
  - very customizable UX/UI
  - *some* level of compatibility with already existing linux applications

The main applications that i have in mind for this operating system are:
  - system recovery usb system things, a secondary operating system for inspecting another system for the purpose of debugging and repair
  - cyberdecks of many varieties
  - capable interface and monitor of the rat nest of arduino projects lurking somewhere in my walls
and (if i do my job right) more!

# that one core chroot feature (explaination)

"Why have different users/environments/installations when you can just take it with you?"

Basically, the idea is to seperate the OS and other higher priveledge code from user space entirely by having them exist entirely seperately. 
When booting into featheros, it will (eventually) scan for userspaces across the connected devices and partitions, or create a "scratch" environment in memory at the user's request. 

For whatever drive the OS is installed on, it will use whatever extra space is available on its disk as a cache for frequently used user/environment files. (Maybe, this might also change depending on the drive speeds connected to the system, as well as how much ram is available to the system)

I think this would be useful because i would find it useful in my own life. I need no more justification. 
