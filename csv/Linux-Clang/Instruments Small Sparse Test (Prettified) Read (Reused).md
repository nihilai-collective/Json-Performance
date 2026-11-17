
----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6898.02 | 0.0549939 | 827.81ms | 7932 | 40 | 14.5481 | 1096.62 | 0.0372216 | 0.774354 | 3.49609 | 0.447428 | 0.000504286 | 6.30358e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6628.12 | 0.0921866 | 828.146ms | 7932 | 160 | 177.109 | 1141.28 | 0.0487628 | 0.804595 | 3.65822 | 0.397504 | 0.00078716 | 9.45537e-06 | 0 | 2(Loss) | true |
