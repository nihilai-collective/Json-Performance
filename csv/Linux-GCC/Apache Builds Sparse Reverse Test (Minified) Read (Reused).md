
----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2201.78 | 0.192172 | 5401.41ms | 94653 | 320 | 1.98632e+06 | 40997.8 | 0.172738 | 2.31509 | 10.8438 | 2.07789 | 0.00686659 | 1.86206e-05 | 1.2975e-05 | 1(Win) | true |
| simdjson (ondemand) | 1791.02 | 0.194846 | 6198.34ms | 94653 | 30 | 289315 | 50400.3 | 0.0338075 | 2.84574 | 11.3914 | 2.081 | 0.00942953 | 3.8738e-05 | 2.99339e-05 | 2(Loss) | true |
