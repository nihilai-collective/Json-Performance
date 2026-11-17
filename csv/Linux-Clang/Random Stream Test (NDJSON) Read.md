
----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1323.68 | 0.107834 | 6029.97ms | 4506447 | 30 | 3.67735e+08 | 3.24676e+06 | 1.17666 | 1.87016 | 1(Win) | true |
| simdjson (ondemand) | 1167.28 | 0.299679 | 6479.99ms | 4506447 | 30 | 3.6522e+09 | 3.68181e+06 | 0.523133 | 2.1209 | 2(Loss) | true |
