
----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 890.594 | 0.0960627 | 8160.54ms | 4506447 | 40 | 8.59566e+08 | 4.82564e+06 | 0.528752 | 2.77995 | 1(Win) | true |
| simdjson (ondemand) | 598.298 | 0.166288 | 5402.1ms | 4506447 | 30 | 4.28035e+09 | 7.18318e+06 | 0.419915 | 4.13809 | 2(Loss) | true |
