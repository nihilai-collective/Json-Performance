
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1577.36 | 0.0562879 | 983.142ms | 4215 | 2560 | 5267.49 | 2548.4 | 0.00821662 | 3.27878 | 14.3535 | 2.82539 | 0.00110904 | 7.92371e-05 | 2.28907e-05 | 1(Win) | true |
| simdjson (reflection) | 1451.2 | 0.047451 | 1002.64ms | 4215 | 2560 | 4422.56 | 2769.95 | 0.00430137 | 3.53313 | 15.3979 | 3.05931 | 0.00110626 | 7.40473e-05 | 1.68668e-05 | 2(Loss) | true |
| Glaze | 929.324 | 0.115943 | 1161.07ms | 4215 | 640 | 16096.6 | 4325.44 | 0.119458 | 5.4815 | 28.0553 | 5.90558 | 0.00359468 | 7.59935e-05 | 1.33452e-05 | 3(Loss) | true |
