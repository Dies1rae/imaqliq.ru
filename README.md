# imaqliq.ru
Client - Server network application for transfer files


SYNOPSIS:

ima_cli  %path_to_transfer_file% %server_ip_address% %server_port%
ima_svc  %ip_adress_to_listen% %port_to_listen%

ima_cli [OPTION]
DESCRIPTION: get local or smb file from path and binary coopy it to stringstream buffer, then it done - translate to server by TCP socket
Return error and type when you forget file(or file is BAD descriptor)\adress\port(or port not INT) or when client can't create socket connection.
Show result of operation.

ima_svc [OPTION]
DESCRIPTION: Start a child proccess and exit prom parrent(kill zombies) and listen client connection with signature like %COMMAND% %FILENAME% %FILE% - so can be tested
from trelnet or whatever... Work with basic errors like creating socket or bad port number. From start show status and PID of proc. To propertly start svc root needed.

ima_svc - starts by default 0.0.0.0 80

ima_svc - 10.10.5.1  - starts with default port 80

ima_svc - 192.168.1.1 666 - starts on users data
