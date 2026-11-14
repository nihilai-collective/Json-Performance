
----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2434.07 | 0.37721 | 189.013ms | 4857 | 4890 | 251968 | 1902.99 | 0.852493 | 1(Win) | true |
| simdjson (ondemand) | 2178.41 | 0.249102 | 223.576ms | 4857 | 4890 | 137189 | 2126.32 | 0.217665 | 2(Loss) | true |
