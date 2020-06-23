#!/bin/bash

if test $# -ne 1                                                        # si le paso mas de un argumento saco un mensaje de error por la salida estandar de errores y le asigno a $? 1 para indicar que hubo un fallo en ejecucion
then
            echo insercion erronea de parametros, ejecucion interrumpida>&2
            exit 1
else
            if test -f $1
            then
                       echo
                       echo ejecucion iniciada
            else                                                        #si el parametro que le paso como entrada no es un fichero saco un mensaje de error por la salida estandar de errores y asigno a $? un 1
                       echo insercion erronea de parametros, ejecucion interrumpida. Debes insertar un fichero como parametro>&2          
                       exit 1
            fi
fi

            echo
            echo se creo un directorio temporal:
            mktemp -d tmpdir.XXX                                        #creo el directorio temporal
            
            cp $1 $(basename ./tmpdir.*)
            cd $(basename ./tmpdir.*)
            
            echo
            
            echo se descomprimieron los siguientes archivos:
            tar -vxf $(basename $1)                                     #descomprimo los archivos, usamos $(basename) para cubrir los hipoteticos casos de que nos pasen un archivo como argumento con una ruta absoluta o relativa
            
            #exit 0
            
            mayores=$(find ./ -name '*' -size +8k)                    # vuelco en encontrados cualquier  archivo superiror al tope
            
            echo
            
            for i in $mayores                                           # recorro mayores y voy eliminado todos los archivos que se pasan del tope
            do
                     echo el archivo $i es mayor de 8KBytes  y se ha eliminado
                     rm $i
                     echo
                     
            done
            
            echo
            echo se volvieron a comprimir los archivos restantes en un zip:
            tar -vzcf $(basename $1) *                                  # ahora le digo  comprimeme todos los archivos restantes en un fichero "*.zip"
            
            #exit 0
            
            cp $(basename $1) ../                                       # copiame el fichero comprimido fuera de la carpeta temporal donde esta "eliminagrandes.sh"
            
            echo
            
            cd ../                                                      # me vuelvo para el directorio posterior
            
            rm -r $(basename ./tmpdir.*)                                # me cargo el directorio temporal
            
            if test $? -ne 1
            then
                    echo ejecucion finalizada con exito
                    echo
                    exit 0                                              # si el programa ha llegado a ejecutar esta linea es que todo salio perfecto
            fi
             
            

       
