
----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10775.4 | 0.233531 | 757.837ms | 2632 | 160 | 47.349 | 232.944 | 0.390562 | 0.551422 | 1.87804 | 0.301292 | 0.000536664 | 4.74924e-06 | 0 | 1(Win) | true |
| Glaze | 3452.87 | 0.136809 | 806.458ms | 2632 | 4890 | 4836.7 | 726.953 | 0.269153 | 1.54754 | 4.84461 | 0.760639 | 0.000387787 | 8.30583e-05 | 1.67049e-05 | 2(Loss) | true |
