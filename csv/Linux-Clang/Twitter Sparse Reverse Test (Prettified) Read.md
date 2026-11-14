
----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5816.37 | 0.0213155 | 6674.74ms | 360584 | 2560 | 406574 | 59122.7 | 0.0233527 | 0.881792 | 4.38275 | 0.665185 | 0.00142728 | 2.07346e-06 | 8.22234e-07 | 1(Win) | true |
| simdjson (ondemand) | 4966 | 0.0326285 | 7688.79ms | 360584 | 2560 | 1.30687e+06 | 69246.8 | 0.11557 | 1.01805 | 5.0342 | 0.704453 | 0.00188925 | 2.13196e-06 | 8.23317e-07 | 2(Loss) | true |
