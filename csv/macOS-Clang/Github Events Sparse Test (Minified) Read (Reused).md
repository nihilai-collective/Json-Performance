
----
### Github Events Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4904.89 | 0.182613 | 1088.57ms | 53331 | 4890 | 1.75337e+06 | 10369.3 | 3.01319 | 1(Win) | true |
| simdjson (ondemand) | 3799.86 | 0.610265 | 1307.83ms | 53331 | 2560 | 1.70805e+07 | 13384.8 | 0.503194 | 2(Loss) | true |
