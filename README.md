ok so making my own bootloader, while fun and interesting, is NOT the way to go for this project. so from now on, im just going to use a bootloader someone else wrote, specifically [Limine](https://github.com/Limine-Bootloader/Limine).

# goals

ok so goals for this project: 
  - Lightweight and portable (small size)
  - that one core chroot feature (will describe better later)
  - Compatibility (performant and not reliant on too many modern CPU features, able to run on older machines)
  - very customizable UX/UI
  - *some* level of compatibility with already existing linux applications
