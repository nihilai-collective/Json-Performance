
----
### Github Events Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8220.37 | 0.0190934 | 1478.17ms | 65103 | 4890 | 10169.4 | 7552.83 | 0.0845422 | 0.629594 | 2.82454 | 0.358279 | 0.000793507 | 2.82704e-06 | 1.91611e-07 | 1(Win) | true |
| simdjson (ondemand) | 7616.71 | 0.0240321 | 1536.04ms | 65103 | 2560 | 9824.1 | 8151.43 | 0.0160606 | 0.679316 | 2.98593 | 0.352703 | 0.000758636 | 3.24006e-06 | 7.50013e-07 | 2(Loss) | true |
