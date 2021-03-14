[Variables]
BLeftX=0
SLeftX=40
FLeftX=80
CenterX=120
FRightX=160
SRightX=200
BRightX=240

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

[LoudnessBGSL]
Meter=Shape
MeterStyle=LevelShapesSL
X=#SLeftX#
Y=0
UpdateDivider=-1
Container=BGMaskSL

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

[LoudnessBGSR]
Meter=Shape
MeterStyle=LevelShapesSR
X=#SRightX#
Y=0
UpdateDivider=-1
Container=BGMaskSR

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

[BGMaskSL]
Meter=Bar
MeterStyle=BarStyles
X=#SLeftX#

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

[BGMaskSR]
Meter=Bar
MeterStyle=BarStyles
X=#SRightX#

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

[LoudnessFillSL]
Meter=Shape
MeterStyle=LevelShapesSL
X=#SLeftX#
Y=0
UpdateDivider=-1
Container=LoudnessMaskSL

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

[LoudnessFillSR]
Meter=Shape
MeterStyle=LevelShapesSR
X=#SRightX#
Y=0
UpdateDivider=-1
Container=LoudnessMaskSR

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

[LoudnessMaskSL]
Meter=Bar
MeasureName=MeasureLoudnessSL
MeterStyle=BarStyle
X=#SLeftX#

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

[LoudnessMaskSR]
Meter=Bar
MeasureName=MeasureLoudnessSR
MeterStyle=BarStyle
X=#SRightX#

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

[StringSL]
Meter=String
MeterStyle=StringStyle
X=(#SLeftX#+5)
Text=SL

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

[StringSR]
Meter=String
MeterStyle=StringStyle
X=(#SRightX#+5)
Text=SR

[StringBR]
Meter=String
MeterStyle=StringStyle
X=(#BRightX#+5)
Text=BR
