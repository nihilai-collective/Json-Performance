
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 503.986 | 0.30062 | 173.486ms | 905 | 80 | 2120.25 | 1712.5 | 0.145773 | 4.83569 | 1(Win) | true |
| Jsonifier (two-stage) | 494.068 | 0.232164 | 182.527ms | 905 | 160 | 2631.68 | 1746.88 | 0.395115 | 4.93035 | 2(Loss) | true |
| Glaze | 490.471 | 0.142734 | 184.265ms | 905 | 640 | 4037.46 | 1759.69 | 0.459608 | 4.9707 | 3(Loss) | true |
| simdjson (ondemand) | 157.352 | 0.167069 | 575.152ms | 905 | 40 | 3358.97 | 5485 | 0.335366 | 15.6502 | 4(Loss) | true |
