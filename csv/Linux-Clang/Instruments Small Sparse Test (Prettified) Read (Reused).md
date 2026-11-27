
----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7123.83 | 0.0680059 | 832.59ms | 7932 | 4890 | 2550 | 1061.86 | 0.017052 | 0.747921 | 3.41301 | 0.450202 | 0.000505447 | 1.39478e-05 | 2.52659e-06 | 1(Win) | true |
| simdjson (ondemand) | 6593.61 | 0.0653649 | 835.366ms | 7932 | 4890 | 2749.9 | 1147.25 | 0.0261857 | 0.808091 | 3.65116 | 0.396117 | 0.000831377 | 1.78924e-05 | 8.86884e-06 | 2(Loss) | true |
