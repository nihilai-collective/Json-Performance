
----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7847.81 | 0.105841 | 5718.18ms | 7351818 | 160 | 1.4306e+08 | 893401 | 0.175055 | 0.655049 | 3.07634 | 0.416909 | 0.00109182 | 0.0635435 | 0.000221472 | 1(Win) | true |
| simdjson (ondemand) | 6135.47 | 0.123685 | 7321.87ms | 7351818 | 160 | 3.19632e+08 | 1.14274e+06 | 0.176708 | 0.836344 | 4.06917 | 0.606493 | 0.000986344 | 0.0847926 | 0.000369267 | 2(Loss) | true |
