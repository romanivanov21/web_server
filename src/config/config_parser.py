import sys
import yaml


def load_config(file_name):
    # type: (object) -> object
    assert isinstance(file_name, object)
    print "load_config"
    result = {}
    try:
        with open(file_name, 'r') as f:
            try:
                result = yaml.load(f)
            except yaml.YAMLError as exc:
                print exc
    except IOError:
        print "Can not find server config file"
    return result


def get_server_name(config):
    result = u''
    try:
        result = config[u'Server'][u'VirtualHost1'][u'Name']
    except KeyError:
        print "Can not parse config file"
    return result

config = load_config(u'/home/roman/work/C++ /web_server/settings/server_config.yaml')
print config
print get_server_name(config)
