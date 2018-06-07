<CsoundSynthesizer>

<CsOptions>
-odac -Ma ;-+rtaudio=jack
</CsOptions>

<CsInstruments>

sr      =       44100
ksmps   =       32
nchnls  =       2
0dbfs   =       1
        seed    0

gisine  ftgen	0,0,4096,10,1

gaSend init 0

gkFreq init 120

gkPlaying init 0

instr 1
    ;printks "Reading midiin", 1
	kstatus, kchan, kdata1, kdata2 midiin
    printk2 kstatus
	if kstatus == 144 then
		printks "Note on\n", 1
        if gkPlaying == 0 then
            printks "triggering event", 1
    		event "i", 2, 0, -1 
            gkPlaying = 1
        endif
	elseif kstatus == 128 then
		printks "Note off\n", 1
		turnoff2 2, 0, 1
        gkPlaying = 0
	elseif kstatus == 176 then
		printks "Control change\n", 1
		gkFreq = kdata2 * 2 + 20
		printks "New freq: %d\n", 1, gkFreq
	endif
endin

 instr 2 ; wgbow instrument
kamp     =        0.1
;kfreq	 =	  p4
kpres    =        0.2
krat     rspline  0.006,0.988,0.1,0.4
kvibf    =        4.5
kvibamp  =        0
iminfreq =        20
aSig	 wgbow    kamp,gkFreq,kpres,krat,kvibf,kvibamp,gisine,iminfreq
aSig     butlp    aSig,2000
aSig     pareq    aSig,80,6,0.707
         outs     aSig,aSig
gaSend   =        gaSend + aSig/3
 endin

 instr 3 ; reverb
aRvbL,aRvbR reverbsc gaSend,gaSend,0.9,7000
            outs     aRvbL,aRvbR
            clear    gaSend
 endin

</CsInstruments>

<CsScore>
i 1 0 3600
; reverb instrument
i 3 0 480
</CsScore>

</CsoundSynthesizer>
