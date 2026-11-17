
----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7770.22 | 0.0959308 | 5773.31ms | 7351818 | 160 | 1.19883e+08 | 902322 | 0.136246 | 0.661236 | 3.0764 | 0.416921 | 0.00101202 | 0.0634845 | 0.000234639 | 1(Win) | true |
| simdjson (ondemand) | 6301.93 | 0.0550951 | 7214.97ms | 7351818 | 320 | 1.20232e+08 | 1.11255e+06 | 0.93694 | 0.808569 | 4.06923 | 0.606508 | 0.000981994 | 0.0848089 | 2.37654e-06 | 2(Loss) | true |
