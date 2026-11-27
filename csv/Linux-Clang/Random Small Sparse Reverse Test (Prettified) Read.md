
----
### Random Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2958.79 | 0.0557497 | 985.218ms | 8150 | 2560 | 5490.51 | 2626.9 | 0.00929472 | 1.76074 | 7.82295 | 1.39877 | 0.00197302 | 4.04045e-05 | 1.24137e-05 | 1(Win) | true |
| simdjson (ondemand) | 2426.89 | 0.0467185 | 1040.91ms | 8150 | 2560 | 5731.04 | 3202.63 | 0.101643 | 2.14254 | 9.21656 | 1.47975 | 0.00400508 | 1.43309e-05 | 2.1089e-06 | 2(Loss) | true |
