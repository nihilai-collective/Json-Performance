
----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8170.3 | 0.0565544 | 935.161ms | 18245 | 160 | 232.094 | 2129.64 | 0.118117 | 0.642462 | 3.30825 | 0.461113 | 0.000164429 | 9.93423e-06 | 1.7128e-06 | 1(Win) | true |
| simdjson (ondemand) | 6316.29 | 0.187093 | 996.153ms | 18245 | 640 | 17000.5 | 2754.75 | 0.0473956 | 0.826204 | 4.27679 | 0.634475 | 0.000339905 | 8.39271e-06 | 8.56399e-08 | 2(Loss) | true |
