
----
### Marine IK Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10752.8 | 0.043858 | 887.406ms | 18245 | 2560 | 1289.38 | 1618.16 | 0.010717 | 0.49108 | 2.43053 | 0.29208 | 0.000123386 | 9.09924e-06 | 1.62716e-06 | 1(Win) | true |
| simdjson (ondemand) | 8763.36 | 0.0965015 | 917.672ms | 18245 | 320 | 1174.8 | 1985.52 | 0.0187329 | 0.59089 | 2.66281 | 0.283804 | 0.000199884 | 5.82351e-06 | 1.7128e-07 | 2(Loss) | true |
