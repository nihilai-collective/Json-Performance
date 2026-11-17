
----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7963.92 | 0.148727 | 3213.58ms | 264040 | 1280 | 2.83056e+06 | 31618.6 | 0.279348 | 0.310616 | 1(Win) | true |
| simdjson (ondemand) | 6966.76 | 0.13789 | 3610.2ms | 264040 | 640 | 1.58972e+06 | 36144.2 | 0.0492541 | 0.355114 | 2(Loss) | true |
