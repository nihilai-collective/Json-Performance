
----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1689.71 | 0.0923911 | 286.863ms | 4926 | 80 | 527.854 | 2780.24 | 0.0346074 | 1(Win) | true |
| simdjson (ondemand) | 1362.04 | 0.078178 | 348.156ms | 4926 | 4890 | 35553.7 | 3449.08 | 0.107505 | 2(Loss) | true |
