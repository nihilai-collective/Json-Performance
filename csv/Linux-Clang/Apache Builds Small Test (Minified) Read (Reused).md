
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2915.26 | 0.0976207 | 827.009ms | 2632 | 4890 | 3454.69 | 861.01 | 0.262991 | 1.81802 | 7.01406 | 1.13336 | 0.000799038 | 4.45982e-05 | 6.21577e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2542.35 | 0.137727 | 841.659ms | 2632 | 2560 | 4733.48 | 987.305 | 0.341933 | 2.08963 | 8.72682 | 1.45175 | 0.000762698 | 9.79531e-05 | 3.1909e-05 | 2(Loss) | true |
| Glaze | 2491.76 | 0.297802 | 840.2ms | 2632 | 40 | 359.977 | 1007.35 | 0.0314455 | 2.10935 | 9.47948 | 1.69947 | 0.00165274 | 1.8997e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 1618.26 | 0.085112 | 919.591ms | 2632 | 4890 | 8522.53 | 1551.1 | 0.119664 | 3.20621 | 11.4669 | 1.89894 | 0.00142015 | 7.0549e-05 | 1.49956e-05 | 4(Loss) | true |
