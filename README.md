# Honeyword-based-authentication-system

An implementation of honeyword-based authentication system that can detect password leaks. The honeword-generation scheme is based on [Erguler's scheme (2)](#erguler).

## About honeywords

Honeywords are fake passwords that are kept along the actual passwords of the users. When a password file is leaked, the adversary tries to crack the hashed passwords and then login into the system. Usually, the time between actual leak and detection of password leak by system admin is too long. It is very likely that the adversary had already caused the damage by then. This scheme tries to reduce that gap.

When the attacker leaks password file from a system that implements Honeyword-scheme, then he gets a list of probable passwords for each user, if he successfully cracks the hashed passwords. Then he needs to figure out the correct passworc, called _sugarword_. If he guesses wrong and enters a honeyword, then the system can detect that a login attempt using a honeyword was made, and some suitable action could be initiated.
      
## Architecture
* **honeychecker program** - It manages the _sugar\_index_ file, which contains usernames and corresponding correct-password index. 
* **server program** - It manipulates the files _F1_ and _F2_. Only this program can directly communicate with the honeychecker program. The _F1_ file contains usernames and corresponding sugarword-index lists. The _F2_ file contains indexes and corresponding passwords (in hashed form).
* **client program** - It interacts with the user, and communicates only with the server program.

  
## References

1. [Honeywords:Making Password-Cracking Detectable, Ari Juels, Ronald L. Rivest](https://people.csail.mit.edu/rivest/pubs/JR13.pdf)

2. <a name="erguler"> [Achieving Flatness: Selecting the Honeywords from Existing User Passwords, Imran Erguler](https://ieeexplore.ieee.org/document/7047759) </a>
  
