
----
### Github Events Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3786.84 | 0.257386 | 58.2274ms | 2158 | 160 | 313.068 | 543.469 | 0.159598 | 1(Win) | true |
| simdjson (ondemand) | 3521.5 | 0.374517 | 66.1707ms | 2158 | 160 | 766.497 | 584.419 | 0.0886847 | 2(Loss) | true |
