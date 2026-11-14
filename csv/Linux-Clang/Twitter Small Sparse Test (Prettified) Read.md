
----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6850.34 | 0.0968448 | 763.469ms | 3770 | 4890 | 1263.34 | 524.843 | 0.0224056 | 0.809048 | 3.25013 | 0.405305 | 0.000306423 | 2.15348e-05 | 2.16975e-06 | 1(Win) | true |
| simdjson (ondemand) | 6618.31 | 0.0552651 | 765.343ms | 3770 | 4890 | 440.756 | 543.243 | 0.0988579 | 0.836828 | 3.31883 | 0.35199 | 0.000358497 | 2.97798e-05 | 5.74984e-06 | 2(Loss) | true |
