from tkinter import *
from tkinter.font import Font
from time import sleep
import serial
import time
import sys
#Se crea un puerto serial para la comunicaion
puerto=serial.Serial()
#para resivir los datos
potenciometros = ["",""]
#Define la velocidad
puerto.baudrate=9600
puerto.timeout=3
# Se define el puerto con el del FTDI
puerto.port='COM3'
def enviado():
    Ent2 = int(Ent.get())
    puerto.close()
    Ent.delete(0,END)
    puerto.open()
    b = chr(Ent2).encode('ascii')
    puerto.write(b)# para codificar y mandar el valor en ASCII

def conexion():
    puerto.open()
    print('Puerto serial listo para la comunicacion')

raiz=Tk()
raiz.title("Comunicacion Serial del PIC16F887")
raiz.geometry("400x300")
raiz.config(bg="Black")
#Creacion de variables para datos
pot1 = StringVar()
pot2 = StringVar()
numero = StringVar()
Ent = Entry(raiz)
#Creacion de botones
Conectar=Button(raiz,text='Conectar',cursor='circle',bg = "Red",fg = "Black",command = conexion)
Enviar=Button(raiz,text='Enviar',cursor='circle',bg = "White",fg = "Red",command = enviado)
#Creacion de etiquetas
et1 = Label(raiz,text = " POT1:",bg = "Red",fg = "Black",width = 15)
et2 = Label(raiz,text = " POT2:",bg = "Red",fg = "Black",width = 15)
et3 = Label(raiz,text = "Contador:",fg = "Red",bg = "Black")
#Creacion de textos para datos que cambian
tx= Label(raiz,textvariable= et1,bg = "Red",fg = "Black",height = 3, width = 15)
tx2= Label(raiz,textvariable= et2,bg = "Red",fg = "Black",height = 3, width = 15)
tx3 = Label(raiz,textvariable = et3,bg = "Black",fg= "White")
#posiciones de los elementos
Enviar.place(x=185,y=157)
Conectar.place(x=50,y=50)
tx.place(x=90,y=218)
tx2.place(x=210,y=218)
tx3.place(x=100,y=150)
et1.place(x=90,y=198)
et2.place(x=210,y=198)
et3.place(x=100,y=120)
Ent.place(x=180,y=120)
raiz.mainloop()

puerto.close()
print('la comunicacion se cancelo')
sys.exit(0)
