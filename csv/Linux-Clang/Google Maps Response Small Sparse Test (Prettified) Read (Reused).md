
----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4031.08 | 0.0252331 | 945.244ms | 9378 | 4890 | 1532.6 | 2218.65 | 0.0203231 | 1.3011 | 5.67402 | 0.943058 | 0.00118404 | 1.26258e-05 | 8.94056e-07 | 1(Win) | true |
| simdjson (ondemand) | 3744.19 | 0.0423363 | 970.341ms | 9378 | 4890 | 5000.79 | 2388.65 | 0.0255323 | 1.39808 | 6.04543 | 0.886863 | 0.00160439 | 1.45666e-05 | 2.81301e-06 | 2(Loss) | true |
