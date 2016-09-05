EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:nightmechanic_lib
LIBS:Cricket-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Cricket noise maker"
Date "2016-09-05"
Rev "0.1"
Comp "Nightmechanics"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Keystone_2468_2xAAA BAT1
U 1 1 57CC72B6
P 1200 1600
F 0 "BAT1" V 1325 1650 60  0000 C CNN
F 1 "Keystone_2468_2xAAA" V 1025 1600 60  0000 C CNN
F 2 "nightmechanic_pcb:Keystone_2468_no_mnt_holes" V 1225 1550 60  0001 C CNN
F 3 "http://www.keyelco.com/product-pdf.cfm?p=1033" V 1325 1650 60  0001 C CNN
	1    1200 1600
	1    0    0    -1  
$EndComp
$Comp
L SPDT_SLIDE SW1
U 1 1 57CC7D12
P 1650 1000
F 0 "SW1" H 1560 1250 60  0000 C CNN
F 1 "SPDT_SLIDE" H 1730 1170 60  0000 C CNN
F 2 "nightmechanic_pcb:ALPS_SSSS810701" H 1650 1000 60  0001 C CNN
F 3 "" H 1650 1000 60  0001 C CNN
	1    1650 1000
	-1   0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD_BD Q1
U 1 1 57CC8172
P 2000 2200
F 0 "Q1" H 2300 2290 50  0000 R CNN
F 1 "Si2312CDS" H 2780 2100 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 2200 2300 50  0000 C CNN
F 3 "" H 2000 2200 50  0000 C CNN
	1    2000 2200
	0    -1   1    0   
$EndComp
$Comp
L GND #PWR01
U 1 1 57CC85B3
P 2900 2300
F 0 "#PWR01" H 2900 2050 50  0001 C CNN
F 1 "GND" H 2900 2150 50  0000 C CNN
F 2 "" H 2900 2300 50  0000 C CNN
F 3 "" H 2900 2300 50  0000 C CNN
	1    2900 2300
	1    0    0    -1  
$EndComp
$Comp
L MSP430G2230ID U1
U 1 1 57CC863E
P 7250 4350
F 0 "U1" H 6250 4800 60  0000 C CNN
F 1 "MSP430G2230ID" H 7900 4800 60  0000 C CNN
F 2 "nightmechanic_pcb:TI-D-SOIC-8" H 6150 4700 60  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/msp430g2230.pdf" H 7250 3900 60  0001 C CNN
	1    7250 4350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 57CC87B4
P 9400 4100
F 0 "#PWR02" H 9400 3850 50  0001 C CNN
F 1 "GND" H 9400 3950 50  0000 C CNN
F 2 "" H 9400 4100 50  0000 C CNN
F 3 "" H 9400 4100 50  0000 C CNN
	1    9400 4100
	1    0    0    -1  
$EndComp
Text Label 8550 4250 0    60   ~ 0
SBWTCK
Text Label 8550 4450 0    60   ~ 0
SBWTDIO
$Comp
L R R5
U 1 1 57CC88ED
P 9800 4150
F 0 "R5" V 9880 4150 50  0000 C CNN
F 1 "47k" V 9800 4150 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 9730 4150 50  0000 C CNN
F 3 "" H 9800 4150 50  0000 C CNN
	1    9800 4150
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 57CC8932
P 9800 4700
F 0 "C2" H 9825 4800 50  0000 L CNN
F 1 "1.8nF" H 9825 4600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9838 4550 50  0000 C CNN
F 3 "" H 9800 4700 50  0000 C CNN
	1    9800 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 57CC8973
P 9800 4950
F 0 "#PWR03" H 9800 4700 50  0001 C CNN
F 1 "GND" H 9800 4800 50  0000 C CNN
F 2 "" H 9800 4950 50  0000 C CNN
F 3 "" H 9800 4950 50  0000 C CNN
	1    9800 4950
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 57CC8B01
P 4950 4250
F 0 "R2" V 5030 4250 50  0000 C CNN
F 1 "1k" V 4950 4250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4880 4250 50  0000 C CNN
F 3 "" H 4950 4250 50  0000 C CNN
	1    4950 4250
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 57CC8C45
P 4950 4450
F 0 "R3" V 5030 4450 50  0000 C CNN
F 1 "1k" V 4950 4450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4880 4450 50  0000 C CNN
F 3 "" H 4950 4450 50  0000 C CNN
F 4 "NA" V 5050 4600 60  0000 C CNN "Assembly"
	1    4950 4450
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 57CC8C7B
P 3300 4500
F 0 "R1" V 3380 4500 50  0000 C CNN
F 1 "1k" V 3300 4500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3230 4500 50  0000 C CNN
F 3 "" H 3300 4500 50  0000 C CNN
	1    3300 4500
	-1   0    0    1   
$EndComp
$Comp
L Q_NPN_BEC Q2
U 1 1 57CC8CCD
P 2750 4250
F 0 "Q2" H 3050 4300 50  0000 R CNN
F 1 "Q_NPN_BEC" H 3350 4200 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 2950 4350 50  0000 C CNN
F 3 "" H 2750 4250 50  0000 C CNN
	1    2750 4250
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 57CC8EF6
P 2900 4800
F 0 "#PWR04" H 2900 4550 50  0001 C CNN
F 1 "GND" H 2900 4650 50  0000 C CNN
F 2 "" H 2900 4800 50  0000 C CNN
F 3 "" H 2900 4800 50  0000 C CNN
	1    2900 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 1100 1200 1100
Wire Wire Line
	1200 2100 1200 2300
Wire Wire Line
	1200 2300 1750 2300
Wire Wire Line
	2000 1000 2000 2000
Wire Wire Line
	2250 2300 2900 2300
Wire Wire Line
	2850 1200 2850 1300
Wire Wire Line
	5700 4050 6000 4050
Wire Wire Line
	5700 3250 5700 4050
Wire Wire Line
	8500 4050 9400 4050
Wire Wire Line
	9400 4050 9400 4100
Wire Wire Line
	8500 4250 8950 4250
Wire Wire Line
	8500 4450 9800 4450
Wire Wire Line
	9800 4300 9800 4550
Wire Wire Line
	9800 4850 9800 4950
Connection ~ 9800 4450
Wire Wire Line
	9800 3350 9800 4000
Wire Wire Line
	6000 4250 5100 4250
Wire Wire Line
	5100 4450 6000 4450
Wire Wire Line
	2650 4450 2650 4700
Wire Wire Line
	2650 4050 2650 3900
Wire Wire Line
	2650 3900 1950 3900
Wire Wire Line
	1900 3350 9800 3350
Connection ~ 5700 3350
$Comp
L C C1
U 1 1 57CC9101
P 3200 3650
F 0 "C1" H 3225 3750 50  0000 L CNN
F 1 "10uF 10V" H 3225 3550 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 3238 3500 50  0000 C CNN
F 3 "" H 3200 3650 50  0000 C CNN
	1    3200 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 3500 3200 3350
Connection ~ 3200 3350
Wire Wire Line
	3200 3800 3200 3900
$Comp
L GND #PWR05
U 1 1 57CC91CB
P 3200 3900
F 0 "#PWR05" H 3200 3650 50  0001 C CNN
F 1 "GND" H 3200 3750 50  0000 C CNN
F 2 "" H 3200 3900 50  0000 C CNN
F 3 "" H 3200 3900 50  0000 C CNN
	1    3200 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 4350 3300 4250
Wire Wire Line
	2950 4250 3650 4250
Wire Wire Line
	2650 4700 3300 4700
Wire Wire Line
	3300 4700 3300 4650
Wire Wire Line
	2900 4800 2900 4700
Connection ~ 2900 4700
$Comp
L POT RV1
U 1 1 57CC94CA
P 3800 4250
F 0 "RV1" H 3800 4170 50  0000 C CNN
F 1 "3.3k POT" H 3800 4250 50  0000 C CNN
F 2 "nightmechanic_pcb:Bourns_TC33X_2" H 3800 4250 50  0000 C CNN
F 3 "" H 3800 4250 50  0000 C CNN
	1    3800 4250
	1    0    0    -1  
$EndComp
Connection ~ 3300 4250
Wire Wire Line
	3950 4250 4800 4250
Wire Wire Line
	3800 4100 4050 4100
Wire Wire Line
	4050 4100 4050 4450
Connection ~ 4050 4250
Wire Wire Line
	4050 4450 4800 4450
$Comp
L CONN_01X02 P1
U 1 1 57CC9871
P 1700 3400
F 0 "P1" H 1700 3550 50  0000 C CNN
F 1 "CONN_01X02" V 1800 3400 50  0000 C CNN
F 2 "Wire_Connections_Bridges:WireConnection_1.20mmDrill" H 1700 3400 50  0000 C CNN
F 3 "" H 1700 3400 50  0000 C CNN
	1    1700 3400
	-1   0    0    1   
$EndComp
Wire Wire Line
	1950 3900 1950 3450
Wire Wire Line
	1950 3450 1900 3450
$Comp
L LED_A1_K2 D1
U 1 1 57CCAD3C
P 8850 5450
F 0 "D1" H 8850 5550 50  0000 C CNN
F 1 "Orange LED" H 8850 5350 50  0000 C CNN
F 2 "nightmechanic_pcb:SMD_MiniLED" H 8850 5450 50  0000 C CNN
F 3 "" H 8850 5450 50  0000 C CNN
	1    8850 5450
	0    -1   -1   0   
$EndComp
$Comp
L R R4
U 1 1 57CCAF8D
P 8850 4900
F 0 "R4" V 8930 4900 50  0000 C CNN
F 1 "330R" V 8850 4900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 8780 4900 50  0000 C CNN
F 3 "" H 8850 4900 50  0000 C CNN
	1    8850 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 4650 8850 4650
Wire Wire Line
	8850 4650 8850 4750
Wire Wire Line
	8850 5650 8850 5750
$Comp
L GND #PWR06
U 1 1 57CCB0C5
P 8850 5750
F 0 "#PWR06" H 8850 5500 50  0001 C CNN
F 1 "GND" H 8850 5600 50  0000 C CNN
F 2 "" H 8850 5750 50  0000 C CNN
F 3 "" H 8850 5750 50  0000 C CNN
	1    8850 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 4650 5350 4650
Wire Wire Line
	5350 4650 5350 5250
Wire Wire Line
	5350 5250 5050 5250
$Comp
L CONN_01X01 P2
U 1 1 57CCB3C4
P 4850 5250
F 0 "P2" H 4850 5350 50  0000 C CNN
F 1 "CONN_01X01" V 4950 5250 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Big" H 4850 5250 50  0000 C CNN
F 3 "" H 4850 5250 50  0000 C CNN
	1    4850 5250
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X04 P3
U 1 1 57CCB827
P 8400 1550
F 0 "P3" H 8400 1800 50  0000 C CNN
F 1 "CONN_01X04" V 8500 1550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 8400 1550 50  0000 C CNN
F 3 "" H 8400 1550 50  0000 C CNN
	1    8400 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 1400 7200 1400
Wire Wire Line
	7200 1400 7200 1050
Wire Wire Line
	8200 1700 7200 1700
Wire Wire Line
	7200 1700 7200 1950
Wire Wire Line
	8200 1500 7200 1500
Wire Wire Line
	8200 1600 7200 1600
Text Label 7600 1500 0    60   ~ 0
SBWTCK
Text Label 7600 1600 0    60   ~ 0
SBWTDIO
$Comp
L GND #PWR07
U 1 1 57CCBCFE
P 7200 1950
F 0 "#PWR07" H 7200 1700 50  0001 C CNN
F 1 "GND" H 7200 1800 50  0000 C CNN
F 2 "" H 7200 1950 50  0000 C CNN
F 3 "" H 7200 1950 50  0000 C CNN
	1    7200 1950
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG08
U 1 1 57CCD3C0
P 2900 2200
F 0 "#FLG08" H 2900 2295 50  0001 C CNN
F 1 "PWR_FLAG" H 2900 2380 50  0000 C CNN
F 2 "" H 2900 2200 50  0000 C CNN
F 3 "" H 2900 2200 50  0000 C CNN
	1    2900 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 2300 2900 2200
$Comp
L PWR_FLAG #FLG09
U 1 1 57CCEA27
P 3550 1050
F 0 "#FLG09" H 3550 1145 50  0001 C CNN
F 1 "PWR_FLAG" H 3550 1230 50  0000 C CNN
F 2 "" H 3550 1050 50  0000 C CNN
F 3 "" H 3550 1050 50  0000 C CNN
	1    3550 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 1300 3550 1050
Wire Wire Line
	2000 1300 3550 1300
Connection ~ 2850 1300
Connection ~ 2000 1300
$Comp
L V_Batt #PWR010
U 1 1 57CD2212
P 7200 1050
F 0 "#PWR010" H 7200 1250 60  0001 C CNN
F 1 "V_Batt" H 7200 1300 60  0000 C CNN
F 2 "" H 7200 1050 60  0000 C CNN
F 3 "" H 7200 1050 60  0000 C CNN
	1    7200 1050
	1    0    0    -1  
$EndComp
$Comp
L V_Batt #PWR011
U 1 1 57CD227B
P 2850 1200
F 0 "#PWR011" H 2850 1400 60  0001 C CNN
F 1 "V_Batt" H 2850 1450 60  0000 C CNN
F 2 "" H 2850 1200 60  0000 C CNN
F 3 "" H 2850 1200 60  0000 C CNN
	1    2850 1200
	1    0    0    -1  
$EndComp
$Comp
L V_Batt #PWR012
U 1 1 57CD238E
P 5700 3250
F 0 "#PWR012" H 5700 3450 60  0001 C CNN
F 1 "V_Batt" H 5700 3500 60  0000 C CNN
F 2 "" H 5700 3250 60  0000 C CNN
F 3 "" H 5700 3250 60  0000 C CNN
	1    5700 3250
	1    0    0    -1  
$EndComp
NoConn ~ 1300 1000
Wire Wire Line
	8850 5050 8850 5250
Text Label 1400 1100 0    60   ~ 0
Bat+
Text Label 1500 2300 0    60   ~ 0
Bat-
$EndSCHEMATC