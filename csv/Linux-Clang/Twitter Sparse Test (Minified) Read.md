
----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7642.48 | 0.25168 | 3339.17ms | 264040 | 640 | 4.40098e+06 | 32948.5 | 0.600074 | 0.323692 | 1(Win) | true |
| simdjson (ondemand) | 6867.41 | 0.0796813 | 3717.04ms | 264040 | 2560 | 2.18528e+06 | 36667.1 | 0.0361186 | 0.360237 | 2(Loss) | true |
