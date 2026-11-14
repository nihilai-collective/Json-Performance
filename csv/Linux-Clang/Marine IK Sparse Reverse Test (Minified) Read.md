
----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3363.51 | 0.167794 | 6710.12ms | 1834197 | 640 | 4.87346e+08 | 520060 | 0.0988655 | 1.51523 | 8.73485 | 1.53934 | 0.00225533 | 0.113182 | 6.19907e-06 | 1(Win) | true |
| simdjson (ondemand) | 2477.26 | 0.128817 | 9277.71ms | 1834197 | 30 | 2.48209e+07 | 706113 | 0.110761 | 2.07004 | 12.6414 | 2.27011 | 0.00381346 | 0.150276 | 1.25395e-06 | 2(Loss) | true |
