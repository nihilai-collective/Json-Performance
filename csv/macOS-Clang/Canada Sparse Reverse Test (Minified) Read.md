
----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3783.89 | 0.83284 | 7545.9ms | 2090234 | 40 | 7.70011e+08 | 526814 | 1.18487 | 1(Win) | true |
| simdjson (ondemand) | 2791.4 | 0.301603 | 9755.26ms | 2090234 | 30 | 1.39168e+08 | 714124 | 0.121139 | 2(Loss) | true |
