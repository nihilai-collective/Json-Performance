
----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2031.7 | 1.09163 | 6162.92ms | 2090234 | 160 | 1.83545e+10 | 981151 | 0.438371 | 2.48337 | 7.66658 | 0.373395 | 0.00031463 | 0.0512681 | 6.18113e-05 | 1(Win) | true |
| Glaze | 1428.27 | 0.237303 | 8875.01ms | 2090234 | 160 | 1.75508e+09 | 1.39568e+06 | 0.0305321 | 3.48081 | 9.59413 | 0.598214 | 0.0115659 | 0.0699955 | 0.00088372 | 2(Loss) | true |
| simdjson (reflection) | 1019.59 | 0.670475 | 6053.54ms | 2090326 | 80 | 1.37477e+10 | 1.95518e+06 | 0.903383 | 5.00034 | 15.154 | 1.43489 | 0.0163984 | 0.0510921 | 0.00396639 | 3(Loss) | true |
