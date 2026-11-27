
----
### Random Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1475.3 | 0.187126 | 5224.39ms | 4506447 | 30 | 8.9145e+08 | 2.91309e+06 | 1.0631 | 1.67813 | 1(Win) | true |
| simdjson (ondemand) | 1377.86 | 0.0885711 | 5479.95ms | 4506447 | 80 | 6.10565e+08 | 3.1191e+06 | 0.436377 | 1.79677 | 2(Loss) | true |
