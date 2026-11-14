
----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3549.91 | 1.0829 | 121.263ms | 3770 | 160 | 19246 | 1012.8 | 1.09375 | 1(Win) | true |
| simdjson (ondemand) | 3187.09 | 0.620614 | 115.621ms | 3770 | 2560 | 125481 | 1128.1 | 0.379724 | 2(Loss) | true |
