
----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3140.19 | 0.0777735 | 817.803ms | 3370 | 2560 | 1622.01 | 1023.47 | 0.00927539 | 1.70317 | 7.37478 | 1.32196 | 0.000597645 | 2.81667e-05 | 8.80935e-06 | 1(Win) | true |
| simdjson (ondemand) | 2677.22 | 0.0530897 | 835.407ms | 3370 | 640 | 259.951 | 1200.45 | 0.296661 | 1.9891 | 7.84777 | 1.35282 | 0.0010701 | 1.48368e-05 | 3.7092e-06 | 2(Loss) | true |
