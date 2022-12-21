# Story  
![Fire_inside_an_abandoned_convent_in_Massueville,_Quebec,_Canada.jpg](https://usercdn.edgeimpulse.com/project160533/ba0d8cfc675ce17a1dbe6f983e93a3921f4b8d275c32c9c369cdee8f5c2333e4)
In order to make the right decision in a fire situation, a fire detection system needs accurate and fast mechanisms. Since most commercial fire detection systems use a simple sensor, their fire recognition accuracy is deficient because of the limitations of the detection capability of the sensor.
Existing devices, which use rule-based algorithms or image-based machine learning can hardly adapt to the changes in the environment because of their static features.

In this project, we develop a device that can detect fire by means of sensor fusion and machine learning.  We will collect the data from the sensors such as temperature, humidity and pressure in various fire situations and extract features to build a machine-learning model to detect the actual fire events. 
After the detection, we will give push notifications to the registered users.   

# Data collection   
To make this project into reality we are using Arduino Nano 33 BLE sense with the Edge Impulse. For the data collection there exist two ways either through the Edge Impulse CLI or through the web browser. 
By using the Edge Impulse CLI follow this [tutorial](https://docs.edgeimpulse.com/docs/development-platforms/officially-supported-mcu-targets/arduino-nano-33-ble-sense).   
Collecting the data from the web browser is actually very simple and straight board, just connect the device with the computer and open up the edge impulse studio and just press the **connect using webusb** and select your developmnet board.
But limitaion of the web serial integration is that it only works with the fully development boards.    
This is our data collection settings. Here we used environmental sensor(temperature+humidty+pressure) because in the case of fire events this parameters will change the most. It ia actually the ** Sensor Fusion **. The sensor data is sampled at 12.5 Hz, bacause parameters are slow moving.   
![Data collection.jpg](https://usercdn.edgeimpulse.com/project160533/11ab431b0d14e003efc6283de66ea4c55e7d3fe4062372f33d799d8ac7a4f063)
We have only two classes in this project **"No Fire"** and **Fire**. For the **No Fire** case, we just collected the data at the different points in the room. For capturing the **Fire** data, we actually build a fire camp like setup in my backyard.To make our model robust we collected the data at different points in that area.
![Fire.jpg](https://usercdn.edgeimpulse.com/project160533/17c4f4f3882f9df6f6817b17baf2061d7640e7b412f0e1d43cf8eef07d2d2649)
The Arduino nano 33 BLE sense can 
13 minutes of data are collected for two labels and split it between the testing and the training. The Edge Impulse has a tool called ** Data Explorer ** which gives you a one-look overview of your complete dataset. 
![Data Explorer.jpg](https://usercdn.edgeimpulse.com/project160533/2fa9c857229c75e9a82c2207a08e264f57e88ae7a37ce66bff8881f4dfdd8fce)
This tool is actually very useful for the object detection based and audio projects.

# Impulse Design  
This is our machine learning pipeline known as Impulse.    
![Impulse.jpg](https://usercdn.edgeimpulse.com/project160533/c40d9b50e1dbc9b3341f9632bd92e351318633d47132505921257460cb17d64b)
For the processing block we used ** Spectral analysis ** and for the learning block we used ** Classification **. **Flatten** and ** Raw Data ** are the other options existing to add as the processing block. Each proceessing block has it's features and uses, if you need to dive into that, please read the tutorial [here](https://docs.edgeimpulse.com/docs/edge-impulse-studio/processing-blocks/custom-blocks).
These are our spectral analysis parameters of **Filter** and **Spectral power**.  We didn't used any filter for the raw data.  
![spectral tab.jpg](https://usercdn.edgeimpulse.com/project160533/bb29bcd9167f16304fdf6b5245b4b2b6c365b87035b4952b46ced549b97e20d3)   
The below image shows the generated features for the collected data, the data is well distinguishable. As you can notice in the case of ** Fire ** event, there is actually three clusters of data and it shows the parameters is changing at different points.
![feature explorer.jpg](https://usercdn.edgeimpulse.com/project160533/e4f3bf8c1a596fdc68a5511e9962e3ddc1f26fe20e641b73a73374c831b72f60)   
After sucessfully extracting the features from the DSP block, it's time to train the machine learning model.  
These are our Neural Network settings and architecture which works very for our data.
![NN network settings and architecture.jpg](https://usercdn.edgeimpulse.com/project160533/2a74f8c66755d30da142a903e5a54dcb1eab74a1e73d9db0cd4bd58dde3bd97d)   
Please read this [guide](https://docs.edgeimpulse.com/docs/edge-impulse-studio/learning-blocks/classification) to know about these affects your model.
After training we hit 98% validation accuracy for the data, that seems to be cool. 
![training output.jpg](https://usercdn.edgeimpulse.com/project160533/f0e0bf461f4b3c610ddd15efc696eea61d97a1210277ed571b9089fb28e324eb)  
The confusion matrix is a good tool for evaluating the model, as you can see below 2.1% is missclassified as ** No Fire **.
![confusion matrix.jpg](https://usercdn.edgeimpulse.com/project160533/8f87b420f27b54be518986e3ee6e4fbd8f324ccbd5272ddfbf829de74d3b579b)  
By checking the feature explorer we can easily identify the sample which is misclassified. It also shows the time at which incorrectly classification happened. Here is one example.    
![feature explorer training.jpg](https://usercdn.edgeimpulse.com/project160533/2bd35f1c1e4471c8576829106c0798bf0f3308c6209e45391e1785018de931d9)  
This machine learning model is well enough for our proejct.Let's see how our model performs on unseen data.
# Model Testing  
Our model performs very well with the unseen data.  
![testing output.jpg](https://usercdn.edgeimpulse.com/project160533/6fe700ead62f576997f3ed7f30cc8930c610d739fa234c4b214ac3ef5e3f4c2d)   
The confusion matrix and feature explorer is also present here to show how our model performs. 
# Live classification   
Now let's test the model with some real-world data. For that we need to move onto the Live Classification tab and connected our arduino using WebUSB.
![No fire 1.jpg](https://usercdn.edgeimpulse.com/project160533/44afb8046e8733f915aa8a7a41b56d88ead4cd3a5f2cadd400ba60f079637cd3)   

The above sample recorded the when there is no fire and below sample recorded when there is fire.     

![Fire_Classification.jpg](https://usercdn.edgeimpulse.com/project160533/427f52db6e5f2fc17153c4975415b7a450b0e9ed160df8a377902d6bea8f4c38)
Real-world data of **No Fire ** and ** Fire ** events are well classified. So our model is ready for deployment

# Hardware   
The Hardware unit consist of a Arduino Nano 33 BLE sense and power adpter. The BLE sense is placed in a 3d printed case.
![hardware.jpg](https://usercdn.edgeimpulse.com/project160533/2942df4afbe50e502ea9b5b3ef1933ebf09934200ac6d2da6b8d03be9860a127)

# Deployment   
We deployed our model in Arduino Nano 33 BLE sense as an arduino library.
![deploy.jpg](https://usercdn.edgeimpulse.com/project160533/4cbae05f8bc68a29244302f0a91e755d373fcfe72a805d5e26026ee512b05ae5)

# Code   
The entire assets for this project are given in this [GitHub repository]().


