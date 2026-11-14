
----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3367.67 | 0.0198692 | 3926.33ms | 94653 | 4890 | 138701 | 26804.3 | 0.221745 | 1.51388 | 7.48562 | 1.35676 | 0.00343324 | 6.82074e-06 | 3.17163e-06 | 1(Win) | true |
| simdjson (ondemand) | 2349.68 | 0.0568688 | 5048.04ms | 94653 | 1280 | 610956 | 38417.2 | 0.0470901 | 2.18651 | 9.07985 | 1.49728 | 0.00601155 | 6.51227e-06 | 3.16947e-06 | 2(Loss) | true |
