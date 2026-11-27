
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 493.86 | 0.457137 | 405.005ms | 1997 | 2560 | 795575 | 3856.33 | 0.222352 | 6.12542 | 1(Win) | true |
| Glaze | 152.52 | 0.907481 | 1144.81ms | 1798 | 40 | 416353 | 11242.5 | 1.10162 | 19.8955 | 2(Loss) | true |
