# Honeyword-based-authentication-system

An implementation of honeyword-based authentication system that can detect password leaks. The honeword-generation scheme is based on [Erguler's scheme (2)](#erguler).

    
      
## Architecture
* **honeychecker program** - It manages the _sugar\_index_ file, which contains usernames and corresponding correct-password index. 
* **server program** - It manipulates the files _F1_ and _F2_. Only this program can directly communicate with the honeychecker program. The _F1_ file contains usernames and corresponding sugarword-index lists. The _F2_ file contains indexes and corresponding passwords (in hashed form).
* **client program** - It interacts with the user, and communicates only with the server program.

  
## References

1. [Honeywords:Making Password-Cracking Detectable, Ari Juels, Ronald L. Rivest](https://people.csail.mit.edu/rivest/pubs/JR13.pdf)

2. <a name="erguler"> [Achieving Flatness: Selecting the Honeywords from Existing User Passwords, Imran Erguler](https://ieeexplore.ieee.org/document/7047759) </a>
  
