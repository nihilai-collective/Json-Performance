
----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1750.9 | 0.501275 | 759.845ms | 905 | 30 | 183.168 | 492.933 | 0.303378 | 3.17937 | 11.0895 | 1.10276 | 0.00445672 | 0 | 0 | 1(Win) | true |
| simdjson (reflection) | 260.054 | 0.0494572 | 1050.98ms | 905 | 2560 | 6897.17 | 3318.84 | 0.129443 | 19.8723 | 94.537 | 21.0276 | 0.0597341 | 0.000124309 | 5.17956e-06 | 2(Loss) | true |
| Glaze | 196.995 | 0.0389734 | 1157.64ms | 905 | 4890 | 14257.1 | 4381.2 | 0.162397 | 26.1306 | 110.857 | 23.4553 | 0.0883289 | 0.000435888 | 0.000180999 | 3(Loss) | true |
