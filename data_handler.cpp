#include "data_handler.hpp"



data_handler::data_handler(QObject *parent) : QObject(parent)
{
    GumboOutput* output = gumbo_parse("<h1>Hello, World!</h1>");
      // Do stuff with output->root
      gumbo_destroy_output(&kGumboDefaultOptions, output);
}


