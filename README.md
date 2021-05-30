# Honeyword-based-authentication-system

An implementation of honeyword-based authentication system that can detect password leaks. The honeword generation scheme is based on [Erguler's scheme (2)](#erguler).

### Architecture
<li> honeychecker program - It contains the username and the corresponding correct-password index (stored in the file sugar_index).
<li> server program - It manipulates the files F1 and F2. Only this program can directly communicate with the honeychecker program.
<li> client program - It interacts with the user. It communicates with the server program.

  
### References

(1) [Honeywords:Making Password-Cracking Detectable, Ari Juels, Ronald L. Rivest](https://people.csail.mit.edu/rivest/pubs/JR13.pdf)

(2) <a name="erguler"> [Achieving Flatness: Selecting the Honeywords from Existing User Passwords, Imran Erguler](https://ieeexplore.ieee.org/document/7047759) </a>
  
