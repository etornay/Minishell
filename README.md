Tu shell deberá:
• Mostrar una entrada mientras espera un comando nuevo.
• Tener un historial funcional.
• Buscar y ejecutar el ejecutable correcto (basado en la variable PATH o mediante el
uso de rutas relativas o absolutas).
• Evita utilizar más de una variable global para indicar la recepción de una señal.
Piensa en lo que implica: Esta aproximación evita que tu gestor de señales acceda
a tus estructuras de datos principales.

• No interpretar comillas sin cerrar o caracteres especiales no especificados en el
enunciado como \ (barra invertida) o ; (punto y coma).
• Gestionar que la ’ evite que el shell interprete los metacaracteres en la secuencia
entrecomillada.
• Gestionar que la " evite que el shell interprete los metacaracteres en la secuencia
entrecomillada exceptuando $ (signo de dólar).
• Implementar redirecciones:
◦ < debe redirigir input.
◦ > debe redirigir output.
◦ “<<” debe recibir un delimitador, después leer del input de la fuente actual
hasta que una línea que contenga solo el delimitador aparezca. Sin embargo,
no necesita actualizar el historial.
◦ “>>” debe redirigir el output en modo append.
• Implementar pipes (carácter |). El output de cada comando en la pipeline se
conecta a través de un pipe al input del siguiente comando.
• Gestionar las variables de entorno ($ seguidos de caracteres) que deberán expandirse a sus valores.
• Gestionar $?, que deberá expandirse al estado de salida del comando más reciente
ejecutado en la pipeline.
• Gestionar ctrl-C ctrl-D ctrl-\, que deberán funcionar como en bash.
• Cuando sea interactivo:
◦ ctrl-C imprime una nueva entrada en una línea nueva.
◦ ctrl-D termina el shell.
◦ ctrl-\ no hace nada.
• Deberá implementar los built-ins:
◦ echo con la opción -n.
◦ cd solo con una ruta relativa o absoluta.
◦ pwd sin opciones.
◦ export sin opciones.

◦ unset sin opciones.
◦ env sin opciones o argumentos.
◦ exit sin opciones.
La función readline puede producir algunos leaks que no necesitas arreglar. Eso no
significa que tu código, sí, el código que has escrito, pueda producir leaks.

Limítate a hacer lo que pide el enunciado. Cualquier cosa no
solicitada no se requiere.
Para cada punto, y en caso de dudas, puedes utilizar _**bash**_ como una
referencia.
