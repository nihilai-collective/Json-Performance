
----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16711.6 | 0.0367995 | 1285.22ms | 94653 | 4890 | 19320.9 | 5401.54 | 0.108317 | 0.30324 | 1.32453 | 0.182678 | 0.000154721 | 4.98862e-06 | 2.31823e-06 | 1(Win) | true |
| Glaze | 6318.66 | 0.0427831 | 2174.29ms | 94653 | 4890 | 182672 | 14286 | 0.0238596 | 0.793699 | 4.32645 | 0.655341 | 5.57888e-05 | 9.28804e-06 | 5.50715e-06 | 2(Loss) | true |
