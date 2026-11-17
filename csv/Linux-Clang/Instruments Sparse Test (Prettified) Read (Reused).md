
----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7065.1 | 0.0248265 | 3213.75ms | 183677 | 2560 | 96994 | 24793.4 | 0.000228451 | 0.728987 | 3.768 | 0.506046 | 0.000416624 | 1.07611e-06 | 4.67873e-08 | 1(Win) | true |
| simdjson (ondemand) | 6596.68 | 0.0907017 | 3399.41ms | 183677 | 160 | 92813.2 | 26554 | 0.0248018 | 0.78166 | 4.00559 | 0.448875 | 0.000989985 | 1.259e-06 | 0 | 2(Loss) | true |
