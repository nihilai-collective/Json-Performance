
----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3979.28 | 0.100326 | 947.199ms | 9378 | 30 | 152.533 | 2247.53 | 0.0355819 | 1.3227 | 5.67402 | 0.943058 | 0.00110542 | 2.13265e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3949 | 0.041239 | 947.746ms | 9378 | 1280 | 1116.54 | 2264.77 | 0.0851045 | 1.32712 | 6.04681 | 0.888036 | 0.00075026 | 1.09965e-05 | 5.83147e-07 | 2(Loss) | true |
