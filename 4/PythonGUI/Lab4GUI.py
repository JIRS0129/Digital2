#Lib imports
import tkinter as tk 
import serial
import struct
import time

while(1): 
    while(1):
        try:    #Port init with defensive programing
            numero = str(int(input(">  COM: ")))
            port = "com" + numero
            break
        except:
            print ("Enter a numeric value")
    try:
        data = serial.Serial(port, baudrate = 9600, timeout=1500)
        break
    except:
        print("Unable to open port")

Main = tk.Tk() #Main window
Main.title("Lab 4 - SPI")
w = 500 
h = 200

ws = Main.winfo_screenwidth()
hs = Main.winfo_screenheight()

x = (ws/2) - (w/2)
y = (hs/2) - (h/2)

Main.geometry('%dx%d+%d+%d' % (w, h, x, y))
Main. config (background = "cyan")

com = tk.Label(Main, text = "COM:" + numero, bg = "blue", fg = "white", font = ("Times New Roman", 20))
com.pack()

contador = 0
data.write(struct.pack('>B',contador)) #Coded data sent

def getSensor(): #Serial read
    if ord(data.read()) == 101: #Start/End byte
        s11 = ord(data.read())  #Save next incoming data to vars
        s12 = ord(data.read())
        s21 = ord(data.read())
        s22 = ord(data.read())

        #Order sensors' value
        if s12 < 10:
            sensor1 = str(s11) + ".0" + str (s12) + "V"
        else:
            sensor1 = str(s11) + "." + str (s12) + "V"

        if s22 < 10:
            sensor2 = str(s21) + ".0" + str (s22) + "V"
        else:
            sensor2 = str(s21) + "." + str (s22) + "V"

        #Send values to labels
        value1.set(sensor1)
        value2.set(sensor2)
    Main.after(10, getSensor) #Repeat after 10ms

def send (): #Funcion
    data.write(struct.pack('>B',int(sensor3.get())))    #Send value on entrybox.

#Construccion general de ventana
name1 = tk.Label(Main, text = "Sensor 1", bg = "blue", fg = "white", font = ("Times New Roman", 14))
name1.place(x = 75, y = 50)

name2 = tk.Label(Main, text = "Sensor 2", bg = "blue", fg = "white", font = ("Times New Roman", 14))
name2.place(x = 220, y = 50)

name3 = tk.Label(Main, text = "TTL", bg = "blue", fg = "white", font = ("Times New Roman", 14))
name3.place(x = 365, y = 50)

#Var for label's text
value1 = tk.StringVar()
value1.set("0")

read1 = tk.Label(Main, textvariable = value1, bg = "blue", fg = "white", font = ("OCR A Extended", 14))
read1.place(x = 75, y = 100)

#Var for label's text
value2 = tk.StringVar()
value2.set("0")

read2 = tk.Label(Main, textvariable = value2, bg = "blue", fg = "white", font = ("OCR A Extended", 14))
read2.place(x = 220, y = 100)

#Button to send data
enviar = tk.Button(Main, text = "Send", command = send)
enviar.place(x = 400, y = 150)

sensor3 = tk.StringVar()
entryBox = tk.Entry(Main, textvariable = sensor3)
entryBox.place(x = 350, y = 100)
sensor3.set("0")

Main.after(10, getSensor)

Main.mainloop()
