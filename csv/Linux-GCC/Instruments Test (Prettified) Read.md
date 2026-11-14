
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2664.29 | 0.0704363 | 6657.28ms | 183677 | 2560 | 5.4901e+06 | 65746.6 | 0.152477 | 0.928867 | 1(Win) | true |
| Jsonifier (generic) | 2425.01 | 0.123494 | 7164.94ms | 183677 | 640 | 5.0928e+06 | 72233.9 | 0.27808 | 1.02053 | 2(Loss) | true |
