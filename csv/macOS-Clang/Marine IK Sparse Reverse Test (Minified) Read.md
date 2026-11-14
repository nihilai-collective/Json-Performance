
----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1850.13 | 0.335154 | 5472.75ms | 1834197 | 320 | 3.2131e+09 | 945459 | 2.48101 | 1(Win) | true |
| simdjson (ondemand) | 1336.1 | 0.438485 | 8530.46ms | 1834197 | 80 | 2.63639e+09 | 1.3092e+06 | 3.24531 | 2(Loss) | true |
