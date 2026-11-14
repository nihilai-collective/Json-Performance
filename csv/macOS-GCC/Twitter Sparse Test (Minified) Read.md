
----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4559.63 | 0.382716 | 6301.17ms | 264040 | 80 | 3.57374e+06 | 55225.6 | 0.185078 | 1(Win) | true |
| simdjson (ondemand) | 3531.45 | 0.721081 | 7919.88ms | 264040 | 30 | 7.93091e+06 | 71304.5 | 0.131469 | 2(Loss) | true |
