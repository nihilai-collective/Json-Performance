
----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3263.89 | 0.115267 | 4012.63ms | 94653 | 160 | 162604 | 27656.7 | 0.00442951 | 1.56755 | 7.4584 | 1.30924 | 0.00345571 | 1.74321e-05 | 1.26119e-05 | 1(Win) | true |
| simdjson (ondemand) | 2344.02 | 0.0986384 | 5140.21ms | 94653 | 160 | 230864 | 38509.9 | 0.00470636 | 2.19305 | 9.08961 | 1.50021 | 0.00676517 | 1.36023e-05 | 9.57445e-06 | 2(Loss) | true |
