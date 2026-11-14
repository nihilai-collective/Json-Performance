
----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2885.83 | 0.044138 | 7777.61ms | 1834197 | 640 | 4.58095e+07 | 606144 | 0.163138 | 1(Win) | true |
| simdjson (ondemand) | 2469.58 | 0.263186 | 9195.93ms | 1834197 | 80 | 2.78011e+08 | 708308 | 0.0347498 | 2(Loss) | true |
