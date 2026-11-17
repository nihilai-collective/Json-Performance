
----
### Github Events Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5574.92 | 0.0208432 | 1634.78ms | 53331 | 4890 | 17681.5 | 9123.07 | 0.193337 | 0.925908 | 4.37635 | 0.713694 | 0.00181953 | 5.98569e-06 | 1.67185e-06 | 1(Win) | true |
| simdjson (ondemand) | 4143.06 | 0.0224469 | 1959.91ms | 53331 | 4890 | 37131.1 | 12276 | 0.000941709 | 1.24094 | 5.90201 | 0.948548 | 0.0022084 | 3.754e-06 | 3.87287e-07 | 2(Loss) | true |
