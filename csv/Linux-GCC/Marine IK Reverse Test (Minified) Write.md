
----
### Marine IK Reverse Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1221.4 | 0.112637 | 9453.37ms | 1922245 | 80 | 2.2864e+08 | 1.50089e+06 | 0.602878 | 2.02698 | 1(Win) | true |
| simdjson (reflection) | 1028.68 | 0.190797 | 5436.54ms | 1922245 | 30 | 3.46833e+08 | 1.78208e+06 | 0.0314402 | 2.40674 | 2(Loss) | true |
| Glaze | 915.077 | 0.310242 | 5945.53ms | 1833577 | 160 | 5.62347e+09 | 1.91092e+06 | 0.0877374 | 2.70553 | 3(Loss) | true |
