[Variables]
BLeftX=0
FLeftX=40
CenterX=80
FRightX=120
BRightX=160

@Include=#@#Meters/_MeterStyles/5.1_7.1_.inc

[BarStyle]
Y=0
W=30
H=125
BarColor=255,255,255
SolidColor=0,0,0,100
BarOrientation=Vertical

[BarStyles]
MeasureName=MeasureBar
Y=0
W=30
H=125
BarColor=255,255,255
SolidColor=0,0,0,10
BarOrientation=Vertical

[StringStyle]
Y=125
FontColor=255,255,255,150
FontFace=Segoe UI
FontSize=12
; StringEffect=Shadow
; FontEffectColor=0,0,0,255
AntiAlias=1
UpdateDivider=-1

; ----------------------------------
; Background -----------------------
; ----------------------------------

[LoudnessBGBL]
Meter=Shape
MeterStyle=LevelShapesBL
X=#BLeftX#
Y=0
UpdateDivider=-1
Container=BGMaskBL

[LoudnessBGFL]
Meter=Shape
MeterStyle=LevelShapesFL
X=#FLeftX#
Y=0
UpdateDivider=-1
Container=BGMaskFL

[LoudnessBGC]
Meter=Shape
MeterStyle=LevelShapesC
X=#CenterX#
Y=0
UpdateDivider=-1
Container=BGMaskC

[LoudnessBGFR]
Meter=Shape
MeterStyle=LevelShapesFR
X=#FRightX#
Y=0
UpdateDivider=-1
Container=BGMaskFR

[LoudnessBGBR]
Meter=Shape
MeterStyle=LevelShapesBR
X=#BRightX#
Y=0
UpdateDivider=-1
Container=BGMaskBR

[BGMaskBL]
Meter=Bar
MeterStyle=BarStyles
X=#BLeftX#

[BGMaskFL]
Meter=Bar
MeterStyle=BarStyles
X=#FLeftX#

[BGMaskC]
Meter=Bar
MeterStyle=BarStyles
X=#CenterX#

[BGMaskFR]
Meter=Bar
MeterStyle=BarStyles
X=#FRightX#

[BGMaskBR]
Meter=Bar
MeterStyle=BarStyles
X=#BRightX#


; ----------------------------------
; Fill -----------------------------
; ----------------------------------


[LoudnessFillBL]
Meter=Shape
MeterStyle=LevelShapesBL
X=#BLeftX#
Y=0
UpdateDivider=-1
Container=LoudnessMaskBL

[LoudnessFillFL]
Meter=Shape
MeterStyle=LevelShapesFL
X=#FLeftX#
Y=0
UpdateDivider=-1
Container=LoudnessMaskFL

[LoudnessFillC]
Meter=Shape
MeterStyle=LevelShapesC
X=#CenterX#
Y=0
UpdateDivider=-1
Container=LoudnessMaskC

[LoudnessFillFR]
Meter=Shape
MeterStyle=LevelShapesFR
X=#FRightX#
Y=0
UpdateDivider=-1
Container=LoudnessMaskFR

[LoudnessFillBR]
Meter=Shape
MeterStyle=LevelShapesBR
X=#BRightX#
Y=0
UpdateDivider=-1
Container=LoudnessMaskBR

; ----------------------------------
; Masks ----------------------------
; ----------------------------------

[LoudnessMaskBL]
Meter=Bar
MeasureName=MeasureLoudnessBL
MeterStyle=BarStyle
X=#BLeftX#

[LoudnessMaskFL]
Meter=Bar
MeasureName=MeasureLoudnessFL
MeterStyle=BarStyle
X=#FLeftX#

[LoudnessMaskC]
Meter=Bar
MeasureName=MeasureLoudnessC
MeterStyle=BarStyle
X=#CenterX#

[LoudnessMaskFR]
Meter=Bar
MeasureName=MeasureLoudnessFR
MeterStyle=BarStyle
X=#FRightX#

[LoudnessMaskBR]
Meter=Bar
MeasureName=MeasureLoudnessBR
MeterStyle=BarStyle
X=#BRightX#


; ----------------------------------
; Text -----------------------------
; ----------------------------------

[StringBL]
Meter=String
MeterStyle=StringStyle
X=(#BLeftX#+5)
Text=BL

[StringFL]
Meter=String
MeterStyle=StringStyle
X=(#FLeftX#+5)
Text=FL

[StringC]
Meter=String
MeterStyle=StringStyle
X=(#CenterX#+7)
Text=C

[StringFR]
Meter=String
MeterStyle=StringStyle
X=(#FRightX#+5)
Text=FR

[StringBR]
Meter=String
MeterStyle=StringStyle
X=(#BRightX#+5)
Text=BR
