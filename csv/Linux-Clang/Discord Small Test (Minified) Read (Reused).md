
----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3168.84 | 0.213482 | 907.357ms | 4857 | 30 | 292.133 | 1461.73 | 0.0205194 | 1.64204 | 6.59049 | 1.24398 | 0.000425503 | 0 | 0 | 1(Win) | true |
| Glaze | 2394.21 | 0.106989 | 953.841ms | 4857 | 4890 | 20950.8 | 1934.67 | 0.158897 | 2.16497 | 8.97735 | 1.62034 | 0.00121638 | 6.3156e-05 | 1.92415e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2100.98 | 0.273276 | 978.506ms | 4857 | 1280 | 46462.8 | 2204.69 | 0.189586 | 2.45037 | 10.4793 | 1.67387 | 0.000934701 | 4.63249e-05 | 1.7211e-05 | 3(Loss) | true |
| simdjson (ondemand) | 883.201 | 0.115245 | 1291.05ms | 4857 | 1280 | 46759.7 | 5244.56 | 0.0265673 | 5.77532 | 21.3967 | 3.45296 | 0.00308157 | 3.08833e-05 | 6.91656e-06 | 4(Loss) | true |
