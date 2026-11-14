
----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3162.64 | 0.0488806 | 761.52ms | 1691 | 4890 | 303.788 | 509.911 | 0.2441 | 1.76479 | 6.86339 | 1.21644 | 0.00156295 | 5.49039e-05 | 2.41868e-06 | 1(Win) | true |
| simdjson (ondemand) | 2557.4 | 0.0603618 | 772.334ms | 1691 | 4890 | 708.471 | 630.587 | 0.390071 | 2.14209 | 8.66292 | 1.43111 | 0.00107812 | 9.75935e-05 | 3.53127e-05 | 2(Loss) | true |
