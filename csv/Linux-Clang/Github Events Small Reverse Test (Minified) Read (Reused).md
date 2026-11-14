
----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1063.79 | 0.0894879 | 878.483ms | 1691 | 1280 | 2355.65 | 1515.95 | 0.0567081 | 4.98116 | 18.9468 | 3.74453 | 0.00177918 | 6.00606e-05 | 4.62005e-07 | 1(Win) | true |
| simdjson (ondemand) | 734.251 | 0.134907 | 947.434ms | 1691 | 80 | 702.353 | 2196.34 | 0.0608598 | 7.14511 | 28.56 | 5.00177 | 0.00441307 | 0.000103489 | 4.43525e-05 | 2(Loss) | true |
