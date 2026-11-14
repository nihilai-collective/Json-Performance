
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4127.09 | 0.142525 | 966.377ms | 9578 | 2560 | 25473.4 | 2213.25 | 0.0278938 | 1.25589 | 5.06786 | 1.0023 | 0.00170904 | 4.51882e-05 | 2.17376e-05 | 1(Win) | true |
| Glaze | 1938.29 | 0.118276 | 1215.88ms | 9578 | 4890 | 151919 | 4712.55 | 0.127737 | 2.63739 | 13.3883 | 2.61067 | 0.00106411 | 7.92332e-05 | 4.67798e-05 | 2(Loss) | true |
