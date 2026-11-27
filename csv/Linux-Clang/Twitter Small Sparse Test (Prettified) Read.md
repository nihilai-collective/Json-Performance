
----
### Twitter Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6925.48 | 0.0577056 | 773.021ms | 3770 | 640 | 57.438 | 519.148 | 0.0562504 | 0.80251 | 3.13316 | 0.402122 | 0.000531333 | 1.28481e-05 | 8.28912e-07 | 1(Win) | true |
| simdjson (ondemand) | 6599.85 | 0.285824 | 776.746ms | 3770 | 80 | 193.956 | 544.763 | 0.163181 | 0.839516 | 3.32493 | 0.35305 | 0.000570292 | 6.29973e-05 | 0 | 2(Loss) | true |
