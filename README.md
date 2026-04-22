ok so making my own bootloader, while fun and interesting, is NOT the way to go for this project. so from now on, im just going to use a bootloader someone else wrote, specifically [Limine](https://github.com/Limine-Bootloader/Limine).

# goals

ok so goals for this project: 
  - Lightweight and portable (small size)
  - that one core chroot feature (will describe better later)
  - Compatibility (performant and not reliant on too many modern CPU features, able to run on older machines)
  - very customizable UX/UI
  - *some* level of compatibility with already existing linux applications


# that one core chroot feature (explaination)

"Why have different users/environments/installations when you can just take it with you?"

Basically, the idea is to seperate the OS and other higher priveledge code from user space entirely by having them exist entirely seperately. 
When booting into featheros, it will (eventually) scan for userspaces across the connected devices, or create a "scratch" environment in memory. 

For whatever drive the OS is installed on, it will use whatever extra space is available on its disk as a cache for frequently used user/environment files. (Maybe, this might depend on if we can read the drive speeds and if it ends up being faster)

I think this would be useful because i would find it useful in my own life. I need no more justification. 
