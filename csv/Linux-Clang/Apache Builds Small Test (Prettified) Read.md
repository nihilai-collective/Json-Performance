
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2834.94 | 0.129898 | 117.012ms | 3370 | 30 | 65.0575 | 1133.67 | 0.0352713 | 0.851236 | 1(Win) | true |
| Jsonifier | 2276 | 0.034124 | 147.066ms | 3370 | 320 | 74.2989 | 1412.07 | 0.223682 | 1.06756 | 2(Loss) | true |
| Glaze | 2216.93 | 0.0588742 | 149.865ms | 3370 | 40 | 29.1385 | 1449.7 | 0.352847 | 1.09631 | 3(Loss) | true |
| simdjson (ondemand) | 1877.88 | 0.0965599 | 173.699ms | 3370 | 80 | 218.477 | 1711.44 | 0.284765 | 1.29794 | 4(Loss) | true |
