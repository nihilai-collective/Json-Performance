
----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1136.57 | 0.286836 | 6445.29ms | 4506447 | 80 | 9.411e+09 | 3.78128e+06 | 0.758236 | 1(Win) | true |
| simdjson (ondemand) | 784.842 | 0.130828 | 8882.6ms | 4506447 | 80 | 4.1058e+09 | 5.47586e+06 | 0.181246 | 2(Loss) | true |
