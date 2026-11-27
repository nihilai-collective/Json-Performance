
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 977.003 | 0.0687599 | 802.575ms | 905 | 4890 | 1804.2 | 883.39 | 0.166357 | 5.50141 | 26.8022 | 4.48398 | 0.00298343 | 0.000138743 | 3.05054e-05 | 1(Win) | true |
| simdjson (ondemand) | 541.511 | 0.0942116 | 881.789ms | 905 | 320 | 721.51 | 1593.83 | 0.131389 | 9.75429 | 50.1282 | 9.45304 | 0.031982 | 4.14365e-05 | 1.03591e-05 | 2(Loss) | true |
