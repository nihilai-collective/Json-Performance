
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1858.61 | 0.0255471 | 7296.79ms | 264040 | 2560 | 3.06682e+06 | 135482 | 0.0110865 | 2.73317 | 10.3744 | 1.96003 | 0.00706331 | 0.000116483 | 9.77006e-06 | 1(Win) | true |
| simdjson (ondemand) | 1616.67 | 0.119046 | 8342.7ms | 264040 | 320 | 1.10022e+07 | 155758 | 0.12885 | 3.13895 | 11.2689 | 1.84299 | 0.0108214 | 0.00024208 | 1.29597e-05 | 2(Loss) | true |
