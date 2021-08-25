# memcorrupt(ctf)

A binary exploitation and memory corruption CTF. Originally built to study for comp6447 final.

## About

Hack these categories three.

+ pwn 
    + Exploitation challenges, read `flag.txt`
+ rev
    + Reverse Engineering challenges, restore the source
+ audit
    + Source code analysis, report the vulnerabilities


## Usage

For the `pwn/` challenges a simple server is included to simulate a real remote server just run the `startpwn` script. You'll probs need socat for this,

```
sudo apt-get socat
```

Then, 

```
sudo ./startpwn
```
