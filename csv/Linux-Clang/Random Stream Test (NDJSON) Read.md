
----
### Random Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 1408.59 | 0.0887917 | 6027.25ms | 4506447 | 80 | 5.87127e+08 | 3.05105e+06 | 5.23298 | 1.75761 | -(Win) | false |
| simdjson (ondemand) | 1227.63 | 0.230355 | 5984.94ms | 4506447 | 80 | 5.20259e+09 | 3.5008e+06 | 0.701034 | 2.0167 | 2(Loss) | true |
