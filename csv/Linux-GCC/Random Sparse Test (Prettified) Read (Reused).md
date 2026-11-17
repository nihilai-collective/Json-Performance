
----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3907.91 | 0.0559933 | 9799.67ms | 676745 | 1280 | 1.09457e+07 | 165151 | 0.0105092 | 1.29516 | 6.17938 | 0.975809 | 0.0027357 | 0.000101796 | 9.52399e-06 | 1(Win) | true |
| simdjson (ondemand) | 3383.16 | 0.033375 | 5584.04ms | 676745 | 640 | 2.59434e+06 | 190767 | 0.269246 | 1.51628 | 6.41586 | 0.975805 | 0.00470732 | 0.00417904 | 8.31185e-07 | 2(Loss) | true |
