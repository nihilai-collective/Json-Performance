
----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4607.41 | 0.054611 | 99.739ms | 4630 | 320 | 87.6514 | 958.35 | 0.0561175 | 1(Win) | true |
| simdjson (ondemand) | 4345.62 | 0.0839794 | 105.71ms | 4630 | 640 | 465.999 | 1016.08 | 0.00615144 | 2(Loss) | true |
