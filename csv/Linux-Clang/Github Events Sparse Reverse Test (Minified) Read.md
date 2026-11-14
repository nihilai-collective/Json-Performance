
----
### Github Events Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5692.12 | 0.0437461 | 1616.51ms | 53331 | 1280 | 19557 | 8935.24 | 0.0158544 | 0.908797 | 4.36592 | 0.711481 | 0.0017715 | 2.98841e-06 | 3.51578e-07 | 1(Win) | true |
| simdjson (ondemand) | 4077.51 | 0.034156 | 1974.57ms | 53331 | 1280 | 23233.5 | 12473.4 | 0.0280769 | 1.26703 | 5.90441 | 0.948079 | 0.00226859 | 4.27753e-06 | 8.20348e-07 | 2(Loss) | true |
