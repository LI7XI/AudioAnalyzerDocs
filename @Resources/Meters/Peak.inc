[Variables]
LeftX=0
RightX=80

@Include=#@#Meters/_MeterStyles/LevelShapes.inc

; ----------------------------------
; Background -----------------------
; ----------------------------------

[PeakBGL]
Meter=Shape
MeterStyle=LevelShapesL
X=#LeftX#
Y=0
UpdateDivider=-1
Container=BGMaskL

[PeakBGR]
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

[PeakLFill]
Meter=Shape
MeterStyle=LevelShapesL
X=#LeftX#
Y=0
Container=PeakLMask
UpdateDivider=-1

[PeakRFill]
Meter=Shape
MeterStyle=LevelShapesR
X=#RightX#
Y=0
Container=PeakRMask
UpdateDivider=-1

; ----------------------------------
; Masks ----------------------------
; ----------------------------------

[PeakLMask]
Meter=Bar
MeasureName=MeasurePeakL
X=#LeftX#
Y=0
W=30
H=125
BarColor=255,255,255,255
; SolidColor=0,0,0
BarOrientation=Vertical

[PeakRMask]
Meter=Bar
MeasureName=MeasurePeakR
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
Text=Peak
UpdateDivider=-1