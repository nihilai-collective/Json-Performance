
----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1964.18 | 0.123277 | 6464.58ms | 2090234 | 30 | 4.69586e+07 | 1.01488e+06 | 0.101215 | 2.56516 | 7.7332 | 0.405686 | 0.000241855 | 0.05061 | 0.000102126 | 1(Win) | true |
| Glaze | 947.214 | 0.375535 | 6522.24ms | 2090234 | 40 | 2.49836e+09 | 2.10449e+06 | 0.177141 | 5.27938 | 9.3422 | 0.534101 | 0.000241349 | 0.0694281 | 0.00122356 | 2(Loss) | true |
