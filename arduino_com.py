#Se der permissao negada para porta basta executar esse comando
#sudo chmod a + rw /dev/ttyACM0

# -*- coding: utf-8 -*-
import serial
from datetime import datetime
import csv
import os

#indica qual arquivo sera escrito 
i = 0

#tamanho maximo do arquivo para escrever noutro
TAM_MAX_ARQUIVO = 32000*8

#taxa leitura/atualizacao
BAUD_RATE = 115200

try:
    arduino = serial.Serial("/dev/ttyACM0",timeout=1, baudrate=BAUD_RATE)
except:
    print('Bad Leke! :(')

while True:
    ft = "teste_cagaco_"
    file_name = ft + str(i) + ".csv"

    v = arduino.readline().split(' ')      
    if ( len(v) == 2):
    	temp_amostra, umidade_amostra = [ k for k in  v ] 
	umidade_amostra = umidade_amostra.replace('\n','').replace('\r','')
	with open( file_name,"a") as f:
           writer = csv.writer(f,delimiter=",")
	   #escreve timestamp, temperatura, amostra
           writer.writerow([datetime.now(), temp_amostra, umidade_amostra])
	   #Apenas no terminal > pode ser comentad
	   print(temp_amostra + ", " + umidade_amostra + " -> arquivo_" + str(i) )
    	   
           #Verificar se e 16 Kb ou KB
           if (os.path.getsize( file_name ) > TAM_MAX_ARQUIVO ):
             i = (1 - i )
	     file_name = ft + str(i) + ".csv"
             with open(file_name, 'w'): pass 

               
