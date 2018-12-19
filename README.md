Our project demostrates the Wireless Display of messages using Wiznet WIZwiki w7500, Max7219 and Smart Phone. It basically connected using the MQTT Protocol.
The MQTT broker will act as an bridge between the Smartphone and Dot Matrix. When an message is sent from the smartphone, the message is sent
to the MQTT broker and the broker will publish the message to the Dot Matrix which is configured with the microcontroller (Wiznet WIZwiki w7500). 
The microcontroller sends the data into the dotmatrix using the MAX7219 library built for Wiznet WIZwiki.


For creating the android application please go this link:
https://github.com/kandilidinesh/ZoNE
