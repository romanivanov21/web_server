#!/usr/bin/python
import yaml

def load_config( file_name ) :
    print "load_config " + file_name
    config = {}
    try:
        with open( file_name, 'r' ) as f :
            try:
                config = yaml.load( f )
            except yaml.YAMLError as exc:
                print exc
    except IOError:
        print "Can not find server config file"
    print config
    return config

def get_virtual_host_name( self ) :
    return self.config[u'Server'][u'VirtualHost1'][u'Name']

def get_server_name(config):
   result = u''
   try:
       result = config[u'Server'][u'VirtualHost1'][u'Name']
   except KeyError:
       print "Can not parse config file"
   return result

def hello() :
    print get_server_name( load_config(u'/home/roman/work/C++ /web_server/settings/server_config.yaml') )
    print "Hello"

hello()
