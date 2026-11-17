
----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2991.3 | 0.0514205 | 6207.43ms | 676745 | 320 | 3.9387e+06 | 215757 | 0.0902885 | 1.69618 | 7.87829 | 1.41069 | 0.00512412 | 0.00095172 | 7.42525e-06 | 1(Win) | true |
| simdjson (ondemand) | 2507.09 | 0.0579461 | 7298.54ms | 676745 | 320 | 7.12047e+06 | 257428 | 0.0608137 | 2.0286 | 9.133 | 1.45794 | 0.00683308 | 0.00339553 | 7.24978e-06 | 2(Loss) | true |
