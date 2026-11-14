
----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2361.3 | 0.0908612 | 1197.67ms | 11812 | 640 | 12024.9 | 4770.58 | 0.155917 | 2.19907 | 10.5319 | 1.9415 | 0.0031713 | 1.15084e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1998.71 | 0.0148347 | 1284.41ms | 11812 | 1280 | 894.781 | 5636.04 | 0.0224194 | 2.59624 | 11.6999 | 1.87343 | 0.00375108 | 1.0384e-05 | 3.30702e-07 | 2(Loss) | true |
