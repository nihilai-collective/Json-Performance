
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2541.9 | 0.0475992 | 5549.37ms | 94653 | 640 | 182865 | 35512 | 0.0255789 | 1.9755 | 9.86479 | 1.56058 | 0.00583241 | 9.60746e-06 | 4.72119e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2067.99 | 0.0352983 | 6381.84ms | 94653 | 2560 | 607746 | 43650.3 | 0.105127 | 2.42663 | 11.7149 | 1.85192 | 0.00654394 | 1.02389e-05 | 5.80657e-06 | 2(Loss) | true |
| Glaze | 2030.53 | 0.0465418 | 6421.13ms | 94653 | 4890 | 2.09337e+06 | 44455.4 | 0.354342 | 2.47504 | 11.754 | 2.2347 | 0.0090867 | 2.08036e-05 | 1.29674e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1919.17 | 0.0603737 | 6733.42ms | 94653 | 160 | 129020 | 47034.9 | 0.00688366 | 2.6353 | 10.6728 | 2.02224 | 0.00719714 | 7.72559e-06 | 4.22596e-06 | 4(Loss) | true |
| simdjson (reflection) | 1807.95 | 0.0693986 | 6978.36ms | 94653 | 640 | 768386 | 49928.6 | 0.0577148 | 2.78986 | 11.1051 | 1.90139 | 0.0043762 | 1.70854e-05 | 1.04163e-05 | 5(Loss) | true |
