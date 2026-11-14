
----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1371.78 | 0.0501745 | 5567.59ms | 4506447 | 80 | 1.97678e+08 | 3.13293e+06 | 0.243497 | 1.8048 | 1(Win) | true |
| simdjson (ondemand) | 1257.21 | 0.181676 | 5938.61ms | 4506447 | 30 | 1.1571e+09 | 3.41844e+06 | 0.0500485 | 1.96927 | 2(Loss) | true |
