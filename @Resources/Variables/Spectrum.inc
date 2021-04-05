[Variables]
Fps=60
UpdateRate=(1000 / #Fps#)
; ------------
BarWidth=3
BarsGab=0.2
; ------------
MaxHeight=100
Color=210,210,230,230
; ------------
; Common settings
; ------------
FreqMin=20
FreqMax=6000
Bands=160
; ------------
; AudioLevel Specfic
; ------------
FFTSize=4096*4
FFTOverlap=((#FFTSize#)/2)
; ------------
FFTAttack=120
FFTDecay=200
; ------------
Sensitivity=45
; ------------
; AudioAnalyzer Specfic
; ------------
BinWidth=3.2
OverlapBoost=5
CascadesCount=1  
; ------------
Attack=60
Decay=45
; ------------
MindB=40
MaxdB=5
; ------------
BlurRadius=1