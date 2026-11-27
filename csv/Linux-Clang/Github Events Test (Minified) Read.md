
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 17299 | 0.0522412 | 1016.91ms | 53331 | 1280 | 3019.64 | 2940.08 | 0.0248779 | 0.301552 | 1.538 | 0.0984231 | 3.82487e-05 | 2.46105e-06 | 2.05087e-07 | 1(Win) | true |
| simdjson (stage-1) | 15204.8 | 0.0510099 | 1045.36ms | 53331 | 30 | 87.3437 | 3345.03 | 0.193696 | 0.343195 | 1.56376 | 0.0663029 | 0.000226885 | 2.50011e-06 | 0 | 2(Loss) | true |
