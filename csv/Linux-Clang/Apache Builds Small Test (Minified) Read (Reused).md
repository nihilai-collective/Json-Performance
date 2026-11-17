
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2940.43 | 0.124435 | 827.283ms | 2632 | 2560 | 2888.51 | 853.642 | 0.0658965 | 1.80421 | 7.01406 | 1.13336 | 0.000763292 | 3.93296e-05 | 3.2651e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2480.52 | 0.133339 | 844.978ms | 2632 | 4890 | 8902.43 | 1011.91 | 0.556024 | 2.14186 | 8.72683 | 1.45175 | 0.00137423 | 5.23679e-05 | 1.12661e-05 | 2(Loss) | true |
| Glaze | 2461.52 | 0.124567 | 841.195ms | 2632 | 2560 | 4130.61 | 1019.73 | 0.328396 | 2.13985 | 9.47948 | 1.69947 | 0.00158461 | 4.68987e-05 | 2.52303e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1635.04 | 0.214515 | 903.428ms | 2632 | 1280 | 13881.6 | 1535.17 | 0.0317146 | 3.17107 | 11.4688 | 1.8997 | 0.00140874 | 5.63972e-05 | 1.48414e-06 | 4(Loss) | true |
