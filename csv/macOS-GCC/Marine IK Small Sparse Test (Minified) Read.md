
----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2876.89 | 0.930236 | 160.921ms | 4604 | 1280 | 258000 | 1526.2 | 0.326541 | 1(Win) | true |
| simdjson (ondemand) | 2371.57 | 0.613244 | 186.392ms | 4604 | 1280 | 164997 | 1851.4 | 1.60502 | 2(Loss) | true |
