[Variables]
X=21

@Include=#@#Meters/_MeterStyles/LevelShapes.inc

; ----------------------------------
; Background -----------------------
; ----------------------------------

[LoudnessBG]
Meter=Shape
MeterStyle=LevelShapes
X=#X#
Y=0
UpdateDivider=-1
Container=BGMask

[BGMask]
Meter=Bar
MeasureName=MeasureBar
X=#X#
Y=0
W=30
H=125
BarColor=255,255,255
SolidColor=0,0,0,100
BarOrientation=Vertical

; ----------------------------------
; Fill -----------------------------
; ----------------------------------

[LoudnessFill]
Meter=Shape
MeterStyle=LevelShapes
X=#X#
Y=0
Container=LoudnessMask
UpdateDivider=-1

; ----------------------------------
; Masks ----------------------------
; ----------------------------------

[LoudnessMask]
Meter=Bar
MeasureName=MeasureLoudness
X=#X#
Y=0
W=30
H=125
BarColor=255,255,255,255
; SolidColor=0,0,0
BarOrientation=Vertical

; ----------------------------------
; Text -----------------------------
; ----------------------------------

[LoudnessdB]
Meter=String
MeasureName=MeasureLoudnessdB
X=12
Y=125
FontColor=255,255,255,150
FontFace=Segoe UI
FontSize=12
; StringAlign=Center
; StringEffect=Shadow
; FontEffectColor=0,0,0,255
NumOfDecimals=1
AntiAlias=1
Text=%1

[StringType]
Meter=String
X=0
Y=20r
FontColor=255,255,255,150
FontFace=Segoe UI
FontSize=12
; StringEffect=Shadow
; FontEffectColor=0,0,0,255
AntiAlias=1
Text=Loudness
UpdateDivider=-1