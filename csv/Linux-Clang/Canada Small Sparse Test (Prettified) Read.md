
----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12713.6 | 0.0433088 | 801.101ms | 11579 | 320 | 45.2805 | 868.569 | 0.0280713 | 0.424059 | 2.10459 | 0.210899 | 0.000172726 | 6.47724e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 11108.3 | 0.129458 | 814.66ms | 11579 | 1280 | 2119.88 | 994.083 | 0.128879 | 0.483033 | 2.36808 | 0.23154 | 0.000173266 | 7.89414e-06 | 8.09655e-07 | 2(Loss) | true |
