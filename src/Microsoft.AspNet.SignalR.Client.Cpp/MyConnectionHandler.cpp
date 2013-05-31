#include "MyConnectionHandler.h"
#include <iostream>

MyConnectionHandler::MyConnectionHandler(void)
{
}


MyConnectionHandler::~MyConnectionHandler(void)
{
}

void MyConnectionHandler::OnError(exception error)
{
    cout << "An error occurred: " << error.what() << endl;
}

void MyConnectionHandler::OnReceived(string_t data)
{
    wcout << data << endl;
}

