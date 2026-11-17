
----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6438.1 | 0.0468326 | 806.713ms | 3873 | 640 | 46.2015 | 573.706 | 0.0413804 | 0.844998 | 3.98502 | 0.476375 | 0.000319116 | 2.33992e-05 | 4.03434e-07 | 1(Win) | true |
| simdjson (reflection) | 3917.38 | 0.127652 | 832.533ms | 3873 | 1280 | 1854.24 | 942.87 | 0.172958 | 1.34415 | 6.77795 | 0.530338 | 0.000590426 | 2.01717e-05 | 2.01717e-06 | 2(Loss) | true |
| Glaze | 2713.62 | 0.0832083 | 886.798ms | 3873 | 80 | 102.617 | 1361.12 | 0.023883 | 1.92424 | 7.8394 | 0.993029 | 0.00422476 | 2.25923e-05 | 3.22747e-06 | 3(Loss) | true |
