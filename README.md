# FH_SAE

## Description:
Measurement loop:
- Current System Time is obtained on client.
- Client sends a message with n * 'c' characters (n defined by BUFF_SIZE) to server.
- Server answers with a message with n * 's' characters (n defined by BUFF_SIZE).
- Current System Time is obtained on client.
- Time difference is stored in array.

Afterwards:
- Array is written to "Measurement.csv" file.

## Info
Adapted from: https://www.geeksforgeeks.org/udp-server-client-implementation-c/

See common.h for some settings
- DEBUG: make sure it is set to 0 for proper tests (otherwise printf will change performance)
- BUFF_SIZE: also defines the number of bytes to be sent

Do not compile with -Wall flag because of "unused variable warning" - sry to lazy to fix

##Network/CPU load
- Network load done with iperf
-- Server: iperf -s
-- Client: iperf -c IP_ADDR -d -t 60000
--- Full-Duplex and long enough to complete the Measurement-loop
-- 270 Mbits/sec throughput without the Measuremtn-loop running
-- 264 Mbits/sec througput with Measurement-loop running
- CPU load done with stress
-- stress -c 16 -i 4 -m 1

## Usage:
- Start server
- Start client
- Copy csv file when done
