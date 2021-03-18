[Variables]
Fps=60
UpdateRate=(1000 / #Fps#)
; ------------
BarWidth=5
BarsGab=0.2
; ------------
MaxHeight=100
Color=210,210,230,230
; ------------
; Common settings
; ------------
FreqMin=20
FreqMax=2000
Bands=60
; ------------
Sensitivity=51
Attack=30
Decay=80
; ------------
; AudioLevel Specfic
; ------------
FFTSize=4096*4
FFTOverlap=((4096*4)/2)
; ------------
; AudioAnalyzer Specfic
; ------------
BinWidth=10
OverlapBoost=10
CascadesCount=3
; ------------
BlurRadius=1
RadiusAdaptation=1