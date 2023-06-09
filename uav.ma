#include(macros.ma)

[top]
components : uav
in : in
out : out
link : out@uav out
link : in in@uav

[uav]
type : cell
dim : (20,20,3)
delay : inertial
defaultDelayTime : 1000
border : wrapped 
neighbors : uav(-1,-1,0) uav(-1,0,0) uav(-1,1,0) 
neighbors : uav(0,-1,0)  uav(0,0,0)  uav(0,1,0)
neighbors : uav(1,-1,0)  uav(1,0,0)  uav(1,1,0)

neighbors : uav(-1,-1,1) uav(-1,0,1) uav(-1,1,1) 
neighbors : uav(0,-1,1)  uav(0,0,1)  uav(0,1,1)
neighbors : uav(1,-1,1)  uav(1,0,1)  uav(1,1,1)

neighbors : uav(-1,-1,2) uav(-1,0,2) uav(-1,1,2) 
neighbors : uav(0,-1,2)  uav(0,0,2)  uav(0,1,2)
neighbors : uav(1,-1,2)  uav(1,0,2)  uav(1,1,2)

initialvalue : 0
initialCellsValue : uav.val
localtransition : uav-layer

in : in
out : out
link : in in@uav(14,12,0) 
link : in in@uav(14,13,0) 
link : in in@uav(14,14,0) 
link : in in@uav(13,13,0) 
link : in in@uav(15,13,0) 
link : out@uav(4,6,0) out
link : out@uav(2,6,0) out
link : out@uav(3,4,0) out
link : out@uav(14,6,0) out
link : out@uav(6,4,0) out
link : out@uav(1,7,0) out

zone : UAV-layer { (0,0,0)..(19,19,0) }
zone : DIF-layer { (0,0,1)..(19,19,1) }
zone : BDR-layer { (0,0,2)..(19,19,2) }


[UAV-layer]
rule : 1 1000 { (0,0,0) = 100 AND #macro(CELL_N_2) < 1000 AND #macro(MAX_NEIGHBOUR_1) = #macro(CELL_N_1) }
rule : 2 1000 { (0,0,0) = 100 AND #macro(CELL_E_2) < 1000 AND #macro(MAX_NEIGHBOUR_1) = #macro(CELL_E_1) }
rule : 3 1000 { (0,0,0) = 100 AND #macro(CELL_S_2) < 1000 AND #macro(MAX_NEIGHBOUR_1) = #macro(CELL_S_1) }
rule : 4 1000 { (0,0,0) = 100 AND #macro(CELL_W_2) < 1000 AND #macro(MAX_NEIGHBOUR_1) = #macro(CELL_W_1) }
rule : 5 1000 { (0,0,0) = 100 AND #macro(CELL_NE_2) < 1000 AND #macro(MAX_NEIGHBOUR_1) = #macro(CELL_NE_1) }
rule : 6 1000 { (0,0,0) = 100 AND #macro(CELL_SE_2) < 1000 AND #macro(MAX_NEIGHBOUR_1) = #macro(CELL_SE_1) }
rule : 7 1000 { (0,0,0) = 100 AND #macro(CELL_SW_2) < 1000 AND #macro(MAX_NEIGHBOUR_1) = #macro(CELL_SW_1) }
rule : 8 1000 { (0,0,0) = 100 AND #macro(CELL_NW_2) < 1000 AND #macro(MAX_NEIGHBOUR_1) = #macro(CELL_NW_1) }
rule : 100 0 { #macro(CELL_S) = 1 }
rule : 100 0 { #macro(CELL_W) = 2 }
rule : 100 0 { #macro(CELL_N) = 3 }
rule : 100 0 { #macro(CELL_E) = 4 }
rule : 100 0 { #macro(CELL_SW) = 5 }
rule : 100 0 { #macro(CELL_NW) = 6 }
rule : 100 0 { #macro(CELL_NE) = 7 }
rule : 100 0 { #macro(CELL_SE) = 8 }
rule : 50 0 { (0,0,0) > 0 }
rule : 0  0 { t }

[DIF-layer]
rule : 0 500 { (0,0,2) = 100 }
rule : { ( ( (1,0,0) + (1,1,0) + (0,1,0) + (-1,0,0) + (0,-1,0) + (-1,1,0) + (-1,-1,0) + (1,-1,0) ) / 8 - (0,0,0) ) / 32 + (0,0,0) } 1000 { t }

[BDR-layer]
rule : { (0,0,0) } 10000 {t}