#!/usr/env python3
# MitM proxy server written for Python 3.5
import multiprocessing as mp
import select
import socket

from OpenSSL import SSL


def handle_client_initiation(connection, address):
    # Create client SSL context
    clsslctx = SSL.Context(SSL.SSLv23_METHOD)
    clsslctx.set_options(SSL.OP_SINGLE_DH_USE)
    clsslctx.use_certificate_file('proxycert.pem')
    clsslctx.use_privatekey_file('proxykey.pem')
    clsslcon = None

    # Create server SSL context
    svsslctx = SSL.Context(SSL.SSLv23_METHOD)
    svsslcon = None

    print('Established connection with {}:{}'.format(address[0], address[1]))
    while True:
        buff = connection.recv(1024)
        if 'CONNECT' in str(buff):
            # Parse the client CONNECT request and make it
            ip, port = str(buff).split(' ')[1].split(':')
            print('CONNECT from {}:{} to {}:{}.'.format(address[0], address[1], ip, port))
            connection.sendall(b'HTTP/1.0 200 Connection established.\r\n\r\n') 

            # Overlay SSL on client-proxy connection
            clsslcon = SSL.Connection(clsslctx, connection)
            clsslcon.set_accept_state()
            print('Created SSL connection with {}:{}'.format(address[0], address[1]))

            # Establish proxy-to-server SSL connection
            svsslcon = SSL.Connection(svsslctx, socket.socket(socket.AF_INET, socket.SOCK_STREAM))
            svsslcon.connect(('127.0.0.1', 8900))
            svsslcon.sendall(b'HTTP/1.0 200 Connection established.\r\n\r\n')
            print('Created SSL connection with {}:{}'.format(ip, port))

            print('Logging all further transactions to file: {}.txt'.format(address[1]))

            clsslcon.setblocking(0)
            svsslcon.setblocking(0)
            with open('{}.txt'.format(address[1]), 'a+') as log:
                while True:
                    try:
                        readers, writers, _ = select.select([clsslcon, svsslcon], [clsslcon, svsslcon], [])
                    except:
                        break

                    clbuff = None
                    svbuff = None
                    for reader in readers:
                        try:
                            if reader == clsslcon:
                                clbuff = reader.recv(1024)
                            if reader == svsslcon:
                                svbuff = reader.recv(1024)
                        except (SSL.WantReadError, SSL.WantWriteError):
                            pass

                    if clbuff:
                        log.write('From {}:\n---\n{}\n\n'.format(clsslcon.getsockname(), str(clbuff)))
                        log.flush()

                    if svbuff:
                        log.write('From {}:\n---\n{}\n\n'.format(svsslcon.getsockname(), str(svbuff)))
                        log.flush()

                    for writer in writers:
                        try:
                            if writer == clsslcon:
                                if svbuff:
                                    clsslcon.sendall(svbuff)
                            if writer == svsslcon:
                                if clbuff:
                                    svsslcon.sendall(clbuff)
                        except (SSL.WantReadError, SSL.WantWriteError):
                            pass


def main():
    # Establish initial server socket
    proxy_sock = socket.socket()
    proxy_sock.bind(('127.0.0.1', 8000))
    proxy_sock.listen(1)

    conns = []
    while True:
        connection, address = proxy_sock.accept()
        proc = mp.Process(target=handle_client_initiation, args=(connection, address))
        proc.daemon = True
        proc.start()


if __name__ == '__main__':
    main()
