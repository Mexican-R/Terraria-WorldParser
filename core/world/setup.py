from distutils.core import setup, Extension
 
module = Extension('WorldParserCore', sources = ['WorldParserCore.cpp'])
setup(name = 'WorldParserCore', version = '1.0', ext_modules = [module])