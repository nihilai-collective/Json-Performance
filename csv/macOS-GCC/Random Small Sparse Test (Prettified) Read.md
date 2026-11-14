
----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2113.92 | 1.69031 | 399.714ms | 8150 | 80 | 309004 | 3676.8 | 0.087108 | 1(Win) | true |
| simdjson (ondemand) | 1721.17 | 0.823512 | 481.217ms | 8150 | 1280 | 1.77019e+06 | 4515.8 | 0.0398442 | 2(Loss) | true |
