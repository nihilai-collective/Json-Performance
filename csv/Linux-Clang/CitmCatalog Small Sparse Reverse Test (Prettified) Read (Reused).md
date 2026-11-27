
----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5330.43 | 0.0682474 | 897.147ms | 9739 | 4890 | 6914.89 | 1742.42 | 0.0497109 | 0.986873 | 4.59195 | 0.758394 | 0.00171488 | 1.59584e-05 | 5.43847e-06 | 1(Win) | true |
| simdjson (ondemand) | 5149.8 | 0.0716798 | 905.303ms | 9739 | 320 | 534.801 | 1803.53 | 0.17305 | 1.02112 | 4.87175 | 0.695657 | 0.00114584 | 9.62624e-06 | 2.88787e-06 | 2(Loss) | true |
