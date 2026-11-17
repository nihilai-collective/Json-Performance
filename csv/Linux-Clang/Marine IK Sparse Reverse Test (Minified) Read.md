
----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3349.76 | 0.14308 | 6751.49ms | 1834197 | 640 | 3.57274e+08 | 522194 | 0.0958524 | 1.53647 | 8.73484 | 1.53934 | 0.00252182 | 0.11316 | 1.93801e-06 | 1(Win) | true |
| simdjson (ondemand) | 2408.53 | 0.289345 | 9231.08ms | 1834197 | 320 | 1.41309e+09 | 726265 | 0.691648 | 2.13301 | 12.6415 | 2.27012 | 0.00357281 | 0.150702 | 2.20464e-06 | 2(Loss) | true |
