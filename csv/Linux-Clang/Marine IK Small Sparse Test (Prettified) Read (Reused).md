
----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11132.4 | 0.0718074 | 884.404ms | 18245 | 80 | 100.772 | 1562.99 | 0.0664234 | 0.474886 | 2.40811 | 0.287038 | 0.000109619 | 1.64429e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 9036.39 | 0.0659288 | 921.556ms | 18245 | 1280 | 2062.8 | 1925.52 | 0.0375974 | 0.581992 | 2.64078 | 0.278871 | 0.000198899 | 8.26425e-06 | 1.32742e-06 | 2(Loss) | true |
