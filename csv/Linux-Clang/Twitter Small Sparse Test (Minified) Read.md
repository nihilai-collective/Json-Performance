
----
### Twitter Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5994.76 | 0.10001 | 769.164ms | 2821 | 320 | 64.4616 | 448.778 | 0.0229738 | 0.921704 | 3.63524 | 0.507621 | 0.000358915 | 4.2095e-05 | 9.96987e-06 | 1(Win) | true |
| simdjson (ondemand) | 5281.08 | 0.34091 | 773.053ms | 2821 | 80 | 241.285 | 509.425 | 0.156794 | 1.03689 | 4.00284 | 0.450904 | 0.00120082 | 8.86211e-06 | 0 | 2(Loss) | true |
