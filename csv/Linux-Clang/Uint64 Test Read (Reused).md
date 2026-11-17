
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3593.23 | 0.121749 | 821.173ms | 3873 | 2560 | 4009.56 | 1027.93 | 0.0283949 | 1.48925 | 7.51975 | 0.938807 | 0.000356636 | 3.89314e-05 | 5.3455e-06 | 1(Win) | true |
| Glaze | 1976.32 | 0.10043 | 909.583ms | 3873 | 2560 | 9018.82 | 1868.92 | 0.193122 | 2.64638 | 14.3085 | 1.78492 | 0.00133708 | 5.5573e-05 | 1.60365e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1676.31 | 0.143238 | 943.996ms | 3873 | 320 | 3187.5 | 2203.39 | 0.14345 | 3.0729 | 13.8136 | 1.58895 | 0.000798799 | 5.56739e-05 | 2.58198e-05 | 3(Loss) | true |
| simdjson (ondemand) | 733.601 | 0.0468631 | 1228.33ms | 3873 | 4890 | 27223.7 | 5034.86 | 0.0290526 | 7.00801 | 27.4216 | 3.45624 | 0.0178619 | 7.41857e-05 | 2.67174e-05 | 4(Loss) | true |
