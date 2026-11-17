
----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12369.3 | 0.178648 | 830.73ms | 11812 | 640 | 1694.09 | 910.708 | 0.0519587 | 0.427452 | 2.04462 | 0.332035 | 8.46597e-05 | 8.99509e-06 | 9.25965e-07 | 1(Win) | true |
| Glaze | 4367.23 | 0.101133 | 997.826ms | 11812 | 4890 | 33275.7 | 2579.39 | 0.226108 | 1.17806 | 5.37437 | 0.765324 | 0.000406436 | 2.51555e-05 | 1.03184e-05 | 2(Loss) | true |
