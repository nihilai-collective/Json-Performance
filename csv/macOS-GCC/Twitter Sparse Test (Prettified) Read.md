
----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4950.06 | 0.640097 | 7677.75ms | 360584 | 30 | 5.93206e+06 | 69469.9 | 0.0981716 | 1(Win) | true |
| simdjson (ondemand) | 3630.03 | 0.253649 | 9556.44ms | 360584 | 2560 | 1.47808e+08 | 94731.8 | 0.617736 | 2(Loss) | true |
