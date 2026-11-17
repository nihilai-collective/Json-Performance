
----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6731.81 | 0.114336 | 766.822ms | 3770 | 320 | 119.325 | 534.084 | 0.0707486 | 0.822692 | 3.30955 | 0.377984 | 0.000265252 | 1.9065e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6662.23 | 0.13316 | 766.862ms | 3770 | 2560 | 1322.01 | 539.662 | 0.00434281 | 0.829796 | 3.42042 | 0.344032 | 0.000309702 | 1.6371e-05 | 3.73011e-06 | 2(Loss) | true |
