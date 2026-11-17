
----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15438 | 0.164561 | 31.033ms | 4669 | 160 | 36.0447 | 288.425 | 0.173656 | 0.145524 | 1(Win) | true |
| simdjson (reflection) | 9049.93 | 0.0683808 | 51.9902ms | 4669 | 320 | 36.2223 | 492.016 | 0.185751 | 0.259133 | 2(Loss) | true |
| Glaze | 1980.16 | 0.111591 | 228.942ms | 4669 | 160 | 1007.46 | 2248.66 | 0.0962609 | 1.23565 | 3(Loss) | true |
