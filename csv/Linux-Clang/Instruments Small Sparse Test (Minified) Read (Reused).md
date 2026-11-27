
----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5157.08 | 0.0750962 | 805.827ms | 4669 | 320 | 134.532 | 863.416 | 0.0459868 | 1.04604 | 4.84108 | 0.706789 | 0.000862069 | 2.20872e-05 | 5.35447e-06 | 1(Win) | true |
| simdjson (ondemand) | 4497.83 | 0.203904 | 821.682ms | 4669 | 30 | 122.24 | 989.967 | 0.0168327 | 1.19355 | 5.35575 | 0.636111 | 0.0013993 | 3.56964e-05 | 7.13929e-06 | 2(Loss) | true |
