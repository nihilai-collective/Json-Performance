
----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8033.02 | 0.0400586 | 5097.73ms | 360584 | 2560 | 752813 | 42808.3 | 8.66873e-05 | 0.635065 | 3.0578 | 0.347961 | 0.00121805 | 9.3804e-06 | 6.93536e-06 | 1(Win) | true |
| simdjson (ondemand) | 7603.26 | 0.0392989 | 5306.73ms | 360584 | 2560 | 808749 | 45227.9 | 0.0534558 | 0.666607 | 3.26327 | 0.326624 | 0.000880166 | 4.83591e-06 | 3.16219e-06 | 2(Loss) | true |
