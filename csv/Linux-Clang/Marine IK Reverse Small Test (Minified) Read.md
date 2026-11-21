
----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 893.76 | 0.0691378 | 499.329ms | 4604 | 80 | 922.892 | 4912.64 | 0.0409826 | 2.75549 | 1(Win) | true |
| Jsonifier (two-stage) | 820.327 | 0.108869 | 539.306ms | 4604 | 30 | 1018.66 | 5352.4 | 0.268512 | 3.00227 | 2(Loss) | true |
| Glaze | 643.925 | 0.583233 | 695.388ms | 4604 | 4890 | 7.73381e+06 | 6818.67 | 0.872956 | 3.82383 | 3(Loss) | true |
| simdjson (ondemand) | 541.85 | 0.124089 | 823.234ms | 4604 | 30 | 3033.2 | 8103.2 | 0.0863111 | 4.55413 | 4(Loss) | true |
