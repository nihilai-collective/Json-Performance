
----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1853.44 | 0.023042 | 5636.15ms | 94653 | 1280 | 161200 | 48703.1 | 0.0442537 | 2.77496 | 12.9834 | 2.53903 | 0.0075906 | 5.35674e-06 | 1.51045e-06 | 1(Win) | true |
| simdjson (ondemand) | 1572.39 | 0.0263098 | 6469.31ms | 94653 | 2560 | 584014 | 57408.3 | 0.0660672 | 3.24804 | 13.6144 | 2.44476 | 0.00820142 | 2.8616e-05 | 1.78613e-05 | 2(Loss) | true |
