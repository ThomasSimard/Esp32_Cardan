
import csv
import os

data = {}

tension_alimentation = 3.3                  #V
resolution_adc = 0.0008056640625            #V

facteur_de_gauge = 2.1                      #
inertie_polaire_du_cardan = 1.91*(10**-8)   #m4 (Hypothese que le cardan est plein)
module_de_cisaillement_acier = 80.0*(10**6)   #Pa

#La mesure est en bit
def Torque(mesure):
    return (2.0 * inertie_polaire_du_cardan * module_de_cisaillement_acier * float(mesure) * resolution_adc) / (facteur_de_gauge * tension_alimentation)

if os.path.exists("data_traiter_esp4.csv"):
    os.remove("data_traiter_esp4.csv")
    
file = open("data_traiter_esp.csv", "a")
file.write("millis,esp2,esp3,esp4,esp5\n")

with open('log.csv', newline='') as csvfile:
    reader = csv.reader(csvfile, delimiter='\n')

    last_line = ["",""]

    esp_last_time = [0,0,0,0]

    for line in reader:
        if(last_line[0] == "Esp"):
            torque_list = list(map(Torque, line[0].split(",")[:-1]))

            time = int(last_line[3])
            delta_time = time - esp_last_time[int(last_line[1]) - 2]
            time_resolution = delta_time / 166 #time increment per mesure

            esp_last_time[int(last_line[1]) - 2] = time

            counter = 0
            for torque in torque_list:
                file.write(str(time + counter * time_resolution))   # Temps
                file.write("," * (int(last_line[1]) - 1)) # Mets la donner dans la colone qui corespond au bon numero de esp
                file.write(str(torque))
                file.write("\n")

                counter += 1

        last_line = line[0].split(",")
        
file.close()