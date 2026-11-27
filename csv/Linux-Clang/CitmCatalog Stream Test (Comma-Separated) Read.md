
----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1261.98 | 0.89053 | 5793.32ms | 4525119 | 30 | 2.78209e+10 | 3.41961e+06 | 0.33316 | 4.01468 | 18.8086 | 3.39521 | 0.0109471 | 0.0775284 | 0.00768154 | 1(Win) | true |
| simdjson (ondemand) | 913.961 | 1.30358 | 7614.99ms | 4525119 | 80 | 3.03088e+11 | 4.72174e+06 | 0.654045 | 5.56407 | 21.744 | 3.56361 | 0.0170871 | 0.0933936 | 0.00791917 | 2(Loss) | true |
