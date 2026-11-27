
----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4040 | 0.0790278 | 780.838ms | 2632 | 4890 | 1178.9 | 621.304 | 0.0407542 | 1.35635 | 5.70555 | 0.93997 | 0.000763763 | 2.9758e-05 | 7.84742e-06 | 1(Win) | true |
| simdjson (ondemand) | 2967.38 | 0.0946322 | 808.31ms | 2632 | 320 | 205.047 | 845.888 | 0.0931842 | 1.81529 | 7.16489 | 1.09422 | 0.000761066 | 3.20574e-05 | 1.18731e-05 | 2(Loss) | true |
