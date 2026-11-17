
----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17949.5 | 0.0493407 | 3298.76ms | 475954 | 30 | 4670.42 | 25287.8 | 0.190768 | 0.28232 | 1.00314 | 0.14775 | 0.000283361 | 0.000983498 | 9.03449e-05 | 1(Win) | true |
| simdjson (reflection) | 11040 | 0.105455 | 4881.5ms | 475954 | 1280 | 2.40625e+06 | 41114.6 | 0.00930222 | 0.455081 | 1.30829 | 0.183753 | 0.000274148 | 0.00170083 | 1.91113e-05 | 2(Loss) | true |
| Glaze | 9052.23 | 0.171625 | 5786.01ms | 475954 | 2560 | 1.89591e+07 | 50142.9 | 0.273434 | 0.555709 | 2.21522 | 0.322105 | 0.000266824 | 0.00299523 | 9.82894e-06 | 3(Loss) | true |
