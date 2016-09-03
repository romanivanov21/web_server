# -*- coding: utf-8 -*-
import yaml

"""
class ConfigParser consists the python class for parsing
server config file from yaml format
"""


class ConfigParser(object):
    def __init__(self):
        self.config = {}
        if __debug__:
            self.debug_module = "Py module error: "

    def __unicode__(self):
        return self.config

    """
    load_config( file_name )

    load and parse yaml file to self.config
    file_name the directory to yaml file
    """

    def load_config(self, file_name):
        res = False

        if (file_name != "") and (file_name is not None):
            try:
                with open(file_name, 'r') as f:
                    try:
                        self.config = yaml.load(f)
                        res = True
                    except yaml.YAMLError as exc:
                        if __debug__:
                            print self.debug_module + exc
            except IOError:
                if __debug__:
                    print self.debug_module + "Can not open server config file: " + file_name
        else:
            if __debug__:
                print self.debug_module + "param file_name is not valid"
        return res

    """
    check_server()

    check is 'Server' in server config file
    return True if 'Server' was found, False - otherwise
    """
    def check_server(self):
        res = False
        try:
            if self.config[u'Server'] is not None:
                res = True
        except KeyError:
            if __debug__:
                print self.debug_module + "Can not found 'Server'"
            else:
                pass
        return res

    """
    check_connection()
    check is 'Connection' in server config file
    return True if 'Connection' was found, False - otherwise
    """
    def check_connection(self):
        res = False
        try:
            if self.config[u'Server'][u'Connection'] is not None:
                res = True
        except KeyError:
            if __debug__:
                print self.debug_module + "Can not found 'Connection'"
            else:
                pass
        return res

    """
    check_directories()
    check is 'Directories' in server config file
    return True if 'Directories' was found, False - otherwise
    """
    def check_directories(self):
        res = False
        try:
            if self.config[u'Server'][u'Directories'] is not None:
                res = True
        except KeyError:
            if __debug__:
                print self.debug_module + "Can not found 'Directories'"
            else:
                pass
        return res

    """
    check_logs()
    check is 'Logs' in server config file
    return True if 'Logs' was found, False - otherwise
    """
    def check_logs(self):
        res = False
        try:
            if self.config[u'Server'][u'Logs'] is not None:
                res = True
        except KeyError:
            if __debug__:
                print self.debug_module + "Can not found 'Logs'"
            else:
                pass
        return res

    """
    get_server_name()

    return server_name from server config file
    if 'Name' was not find in file, return empty string
    """

    def get_server_name(self):
        result = u''

        try:
            result = self.config[u'Server'][u'Name']
        except KeyError:
            if __debug__:
                print self.debug_module + "Can not find 'Name' "
            else:
                pass
        return result

    """
    get_ip_version()

    return ip_version from server config file
    if 'ip_version' was not find in file, return empty string
    """

    def get_ip_version(self):
        res = u''

        try:
            res = self.config[u'Server'][u'Connection'][u'ip_version']
        except KeyError:
            if __debug__:
                print self.debug_module + "Can not find 'ip_version"
            else:
                pass
        return res

    """
    get_ip_address()

    return 'ip_address' from server config file
    if 'ip_address was not find in file, return empty string'
    """

    def get_ip_address(self):
        res = u''

        try:
            res = self.config[u'Server'][u'Connection'][u'ip_address']
        except KeyError:
            if __debug__:
                print self.debug_module + "Can not find 'ip_address' "
            else:
                pass
        return res

    """
    get_listen()

    return 'listen' from server config file
    if 'listen' was not find in file, return empty string
    """
    def get_listen(self):
        res = 0

        try:
            res = self.config[u'Server'][u'Connection'][u'listen']
        except KeyError:
            if __debug__:
                print self.debug_module + "Can not find 'listen' "
            else:
                res = None
        return res

    """
    get_document_root()

    return 'document_root' form server config file
    if 'document_root' was not find, return empty string
    """

    def get_document_root(self):
        res = u''

        try:
            res = self.config[ u'Server' ][ u'Directories' ][ u'document_root' ]
        except KeyError:
            if __debug__:
                print self.debug_module + "Can not find 'document_root' "
            else:
                pass
        return res

    """
    get_access_log()

    return 'access_log' from server config file
    if 'access_log' was not find, return empty string
    """
    def get_access_log(self):
        res = u''

        try:
            res = self.config[ u'Server' ][ u'Logs'][u'access_log']
        except KeyError:
            if __debug__:
                print self.debug_module + "Can not find 'access_log' "
            else:
                pass
        return res

    """
    get_error_log()

    return 'error_log' form server config file
    if 'error_log' was not found, return empty string
    """
    def get_error_log(self):
        res = u''

        try:
            res = self.config[ u'Server' ][ u'Logs' ][ u'error_log' ]
        except KeyError:
            if __debug__:
                print self.msg_name + "Can not found 'error_log' "
            else:
                pass
        return res

    """
    get_modules()

    return dictionary of modules
    """
    def get_modules(self):
        res = []
        try:
            res = self.config[ u'Modules' ]
        except KeyError:
            if __debug__:
                print self.debug_module + "Can not found modules"
            else:
                pass
        return res
