import io
import os
import serial
import time
import syslog

# Imports the Google Cloud client library
from google.cloud import vision
from google.cloud.vision import types
from google.oauth2 import service_account
 
 #Global Variables
labelArray = [] #represented as unicode string 
RecyclableItems = ['Plastic','Cardboard','Aluminum', 'Can', 'Steel','Glass','Metal',"Paper","Textile","Textiles","Electronics"]#Common recycalble materials 
SensorOn = True #Tells if sensor is fetching data
arduinoSerial = serial.Serial('/dev/tty.usbmodem14201',9600)

while SensorOn:
     
    SensorCommunicationDistance = arduinoSerial.readline()

    
 
    if((int(SensorCommunicationDistance)<20)):
         
         
    
    
    # Instantiates a client
        credentials = service_account.Credentials.from_service_account_file('/Users/AmiteshThind/SaveEarth/VisionApp-ca01261c91b4.json')
        client = vision.ImageAnnotatorClient(credentials=credentials)
        # The name of the image file to annotate


        #if data recieved from ardunio is true then run below

        file_name = os.path.join(
        os.path.dirname(__file__),
        '/Users/AmiteshThind/Desktop/Object.jpg') #path to where image taken by camera is stored 

        # Loads the image into memory
        with io.open(file_name, 'rb') as image_file:
            content = image_file.read()

        image = types.Image(content=content)

        # Performs label detection on the image file
        response = client.label_detection(image=image)
        labels = response.label_annotations

        print('Labels:')
        for label in labels:
            itemDescription = label.description
            labelArray.append(itemDescription)

        print(labelArray)

        for i in labelArray:

            if (i in RecyclableItems):

                ItemRecycalble = True
                break
                 
      
            else:
                pass
    

        if(ItemRecycalble): 
            
            print ("Recycling")
            arduinoSerial.write('1')
             
             

  
        else:
             
            print("Garbage") 
            arduinoSerial.write('0')
            
        time.sleep(3)       
         
        




