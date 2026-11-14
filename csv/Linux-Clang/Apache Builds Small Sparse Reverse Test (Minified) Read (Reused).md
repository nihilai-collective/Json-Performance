
----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2843.9 | 0.0576186 | 808.122ms | 2632 | 1280 | 331.039 | 882.616 | 0.0361896 | 1.89392 | 8.40008 | 1.52432 | 0.0011413 | 4.83829e-05 | 5.93655e-07 | 1(Win) | true |
| simdjson (ondemand) | 2438.89 | 0.0427152 | 819.476ms | 2632 | 4890 | 945.064 | 1029.19 | 0.0125057 | 2.194 | 9.06079 | 1.45935 | 0.00114495 | 4.63852e-05 | 1.99682e-05 | 2(Loss) | true |
