[top]
components : dif
in : in
out : out
link : out@dif out
link : in in@dif

[dif]
type : cell
dim : (20,20,1)
delay : inertial
defaultDelayTime : 1000
border : wrapped 
neighbors : dif(-1,-1,0) dif(-1,0,0) dif(-1,1,0) 
neighbors : dif(0,-1,0)  dif(0,0,0)  dif(0,1,0)
neighbors : dif(1,-1,0)  dif(1,0,0)  dif(1,1,0)

neighbors : dif(-1,-1,1) dif(-1,0,1) dif(-1,1,1) 
neighbors : dif(0,-1,1)  dif(0,0,1)  dif(0,1,1)
neighbors : dif(1,-1,1)  dif(1,0,1)  dif(1,1,1)

neighbors : dif(-1,-1,2) dif(-1,0,2) dif(-1,1,2) 
neighbors : dif(0,-1,2)  dif(0,0,2)  dif(0,1,2)
neighbors : dif(1,-1,2)  dif(1,0,2)  dif(1,1,2)

initialvalue : 0
initialCellsValue : diffusionTest.val
localtransition : dif-layer

in : in
out : out
link : in in@dif(14,12,0) 
link : in in@dif(14,13,0) 
link : in in@dif(14,14,0) 
link : in in@dif(13,13,0) 
link : in in@dif(15,13,0) 
link : out@dif(4,6,0) out
link : out@dif(2,6,0) out
link : out@dif(3,4,0) out
link : out@dif(14,6,0) out
link : out@dif(6,4,0) out
link : out@dif(1,7,0) out

zone : DIF-layer { (0,0,0)..(19,19,0) }

[DIF-layer]
rule : 0 500 { (0,0,2) = 100 }
rule : { ( ( (1,0,0) + (1,1,0) + (0,1,0) + (-1,0,0) + (0,-1,0) + (-1,1,0) + (-1,-1,0) + (1,-1,0) ) / 8 - (0,0,0) ) / 32 + (0,0,0) } 1000 { t }
