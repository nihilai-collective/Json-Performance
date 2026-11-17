
----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4880.6 | 0.0962696 | 805.578ms | 4669 | 2560 | 1974.78 | 912.327 | 0.245511 | 1.09996 | 4.89848 | 0.701007 | 0.00140663 | 2.09995e-05 | 3.93219e-06 | 1(Win) | true |
| simdjson (ondemand) | 4532.19 | 0.0768565 | 816.019ms | 4669 | 4890 | 2788.06 | 982.463 | 0.348185 | 1.18911 | 5.36539 | 0.639966 | 0.00126685 | 1.96659e-05 | 3.46015e-06 | 2(Loss) | true |
