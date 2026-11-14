
----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1843.06 | 0.0551153 | 5593.97ms | 409725 | 320 | 4.36917e+06 | 212008 | 0.296108 | 2.76936 | 12.8282 | 2.46445 | 0.00881192 | 3.37116e-05 | 4.10336e-06 | 1(Win) | true |
| simdjson (ondemand) | 1477.27 | 0.0583821 | 6955.98ms | 409725 | 160 | 3.81544e+06 | 264504 | 0.0959933 | 3.47948 | 15.3611 | 2.62544 | 0.0122444 | 0.000391635 | 6.8186e-06 | 2(Loss) | true |
