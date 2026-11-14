
----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2125.59 | 0.520916 | 7943.85ms | 676745 | 160 | 4.00265e+08 | 303631 | 3.57429 | 1(Win) | true |
| simdjson (ondemand) | 1349.79 | 0.836166 | 5791.87ms | 676745 | 80 | 1.27878e+09 | 478145 | 2.01184 | 2(Loss) | true |
