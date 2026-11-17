
----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1791.92 | 0.128243 | 7251.36ms | 4197496 | 30 | 2.46224e+08 | 2.23394e+06 | 0.285 | 1.38162 | 1(Win) | true |
| simdjson (ondemand) | 1774.3 | 0.183716 | 7336.07ms | 4197496 | 30 | 5.15395e+08 | 2.25612e+06 | 0.543977 | 1.39534 | 2(Loss) | true |
