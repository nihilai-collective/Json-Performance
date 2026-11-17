
----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5168.26 | 0.0845135 | 790.332ms | 3770 | 1280 | 442.442 | 695.66 | 0.25163 | 1.05441 | 4.49576 | 0.667639 | 0.000573193 | 4.80769e-05 | 1.59566e-05 | 1(Win) | true |
| simdjson (ondemand) | 4685.34 | 0.0707849 | 794.95ms | 3770 | 640 | 188.826 | 767.362 | 0.0065154 | 1.15582 | 4.96313 | 0.680371 | 0.000707062 | 1.53349e-05 | 4.14456e-07 | 2(Loss) | true |
