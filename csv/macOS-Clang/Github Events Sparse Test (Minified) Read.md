
----
### Github Events Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4579.74 | 0.249129 | 1147.08ms | 53331 | 4890 | 3.74315e+06 | 11105.5 | 1.82182 | 1(Win) | true |
| simdjson (ondemand) | 4000.63 | 0.426402 | 1343.86ms | 53331 | 1280 | 3.7614e+06 | 12713.1 | 0.99346 | 2(Loss) | true |
