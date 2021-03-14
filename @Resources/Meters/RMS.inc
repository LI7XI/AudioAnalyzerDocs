[Variables]
LeftX=0
RightX=80

@Include=#@#Meters/_MeterStyles/LevelShapes.inc

; ----------------------------------
; Background -----------------------
; ----------------------------------

[RMSBGL]
Meter=Shape
MeterStyle=LevelShapesL
X=#LeftX#
Y=0
UpdateDivider=-1
Container=BGMaskL

[RMSBGR]
Meter=Shape
MeterStyle=LevelShapesR
X=#RightX#
Y=0
UpdateDivider=-1
Container=BGMaskR

[BGMaskL]
Meter=Bar
MeasureName=MeasureBar
X=#LeftX#
Y=0
W=30
H=125
BarColor=255,255,255
SolidColor=0,0,0,100
BarOrientation=Vertical

[BGMaskR]
Meter=Bar
MeasureName=MeasureBar
X=#RightX#
Y=0
W=30
H=125
BarColor=255,255,255
SolidColor=0,0,0,100
BarOrientation=Vertical

; ----------------------------------
; Fill -----------------------------
; ----------------------------------

[RMSLFill]
Meter=Shape
MeterStyle=LevelShapesL
X=#LeftX#
Y=0
Container=RMSLMask
UpdateDivider=-1

[RMSRFill]
Meter=Shape
MeterStyle=LevelShapesR
X=#RightX#
Y=0
Container=RMSRMask
UpdateDivider=-1

; ----------------------------------
; Masks ----------------------------
; ----------------------------------

[RMSLMask]
Meter=Bar
MeasureName=MeasureRMSL
X=#LeftX#
Y=0
W=30
H=125
BarColor=255,255,255,255
; SolidColor=0,0,0
BarOrientation=Vertical

[RMSRMask]
Meter=Bar
MeasureName=MeasureRMSR
X=#RightX#
Y=0
W=30
H=125
BarColor=255,255,255,255
; SolidColor=0,0,0
BarOrientation=Vertical

; ----------------------------------
; Text -----------------------------
; ----------------------------------

[StringLeft]
Meter=String
X=(#LeftX#+8)
Y=125
FontColor=255,255,255,150
FontFace=Segoe UI
FontSize=12
; StringEffect=Shadow
; FontEffectColor=0,0,0,255
AntiAlias=1
Text=L
UpdateDivider=-1

[StringRight]
Meter=String
X=(#RightX#+7)
Y=125
FontColor=255,255,255,150
FontFace=Segoe UI
FontSize=12
; StringEffect=Shadow
; FontEffectColor=0,0,0,255
AntiAlias=1
Text=R
UpdateDivider=-1

[StringType]
Meter=String
X=35
Y=125
FontColor=255,255,255,150
FontFace=Segoe UI
FontSize=12
; StringEffect=Shadow
; FontEffectColor=0,0,0,255
AntiAlias=1
Text=RMS
UpdateDivider=-1