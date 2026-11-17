
----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8274.78 | 0.0863725 | 5014.8ms | 360584 | 80 | 103072 | 41557.6 | 0.0739991 | 0.622754 | 2.93767 | 0.358152 | 0.000752113 | 1.31731e-06 | 7.27986e-07 | 1(Win) | true |
| simdjson (ondemand) | 7529.62 | 0.0314951 | 5424.03ms | 360584 | 2560 | 529654 | 45670.3 | 0.0902102 | 0.671355 | 3.1352 | 0.32199 | 0.00104077 | 1.88496e-06 | 8.6015e-07 | 2(Loss) | true |
