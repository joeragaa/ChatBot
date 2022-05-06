# ChatBot
Embedded microcontrollers Chatbot implementation with two PCs and two TivaC microcontrollers
The end goal of this project is to create a chatting system between two PCs. The system consists of A PC connected with 
a TivaC microcontroller utilizing UART serial communication. The two microcontrollers are connected using CAN communication.
The messages are sent from one PC to its corresponding TivaC and hence encrypted and packaged for CAN communication. The opposing Tiva recieves the message,
decrypts it and displays it on the corresponding PC.
