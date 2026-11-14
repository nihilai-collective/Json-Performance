
----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5206.46 | 0.0210593 | 4105.95ms | 183677 | 2560 | 128515 | 33644.4 | 0.05501 | 0.987566 | 5.4911 | 0.87153 | 0.000745277 | 1.85235e-06 | 1.48869e-07 | 1(Win) | true |
| simdjson (ondemand) | 4163.7 | 0.0879907 | 4945.12ms | 183677 | 320 | 438504 | 42070.3 | 0.00210218 | 1.23287 | 6.49051 | 0.932126 | 0.00177256 | 3.02841e-06 | 6.97556e-07 | 2(Loss) | true |
