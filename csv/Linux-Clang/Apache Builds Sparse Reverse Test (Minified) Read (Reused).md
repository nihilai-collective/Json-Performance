
----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2233.03 | 0.0657659 | 5223.24ms | 94653 | 320 | 226168 | 40424.1 | 0.218381 | 2.27722 | 11.1128 | 2.11506 | 0.0063194 | 3.16947e-06 | 1.65077e-07 | 1(Win) | true |
| simdjson (ondemand) | 1856.57 | 0.0190532 | 6079.28ms | 94653 | 4890 | 419655 | 48620.9 | 0.0284297 | 2.75974 | 11.7615 | 2.0258 | 0.00725374 | 4.40096e-06 | 1.06513e-06 | 2(Loss) | true |
