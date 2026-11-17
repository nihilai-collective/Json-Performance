
----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2217.52 | 0.0168181 | 5327.2ms | 94653 | 4890 | 229192 | 40706.9 | 0.234859 | 2.29423 | 11.1172 | 2.11621 | 0.00642908 | 1.39159e-05 | 9.74391e-06 | 1(Win) | true |
| simdjson (ondemand) | 1823.61 | 0.0704013 | 6166.43ms | 94653 | 320 | 388612 | 49499.7 | 0.00729856 | 2.78356 | 11.8004 | 2.0392 | 0.00811131 | 1.84226e-05 | 9.31032e-06 | 2(Loss) | true |
