
----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3062.65 | 0.115641 | 793.853ms | 25388 | 30 | 2507.29 | 7905.53 | 0.00716849 | 0.80576 | 1(Win) | true |
| simdjson (reflection) | 2847.35 | 0.108302 | 860.339ms | 25388 | 40 | 3392.42 | 8503.3 | 0.00156799 | 0.866723 | 2(Loss) | true |
| Jsonifier (two-stage) | 2818.94 | 0.0931758 | 874.807ms | 25388 | 30 | 1921.38 | 8589 | 0.129013 | 0.87537 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 2339.82 | 0.429449 | 1055.54ms | 25388 | 320 | 631926 | 10347.8 | 0.470433 | 1.0553 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 2336.29 | 0.132638 | 1047.37ms | 25388 | 2560 | 483702 | 10363.4 | 0.168545 | 1.05701 | 4(Tie) | true |
