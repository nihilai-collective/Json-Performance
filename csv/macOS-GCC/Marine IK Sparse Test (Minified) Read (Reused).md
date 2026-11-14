
----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 2739.93 | 0.158065 | 8212.02ms | 1834197 | 40 | 4.07328e+07 | 638419 | 0.0491455 | 1(Win) | true |
| Jsonifier (generic) | 2576.6 | 0.243485 | 8941.37ms | 1834197 | 320 | 8.74366e+08 | 678889 | 1.96563 | 2(Loss) | true |
