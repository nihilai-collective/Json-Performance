
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2192.21 | 0.130017 | 773.015ms | 1213 | 4890 | 2301.8 | 527.691 | 0.198847 | 2.50663 | 12.0998 | 1.97115 | 0.00191214 | 0.000124419 | 2.30968e-05 | 1(Win) | true |
| simdjson (reflection) | 1093.72 | 0.200531 | 832.012ms | 1213 | 320 | 1439.54 | 1057.68 | 0.866935 | 4.89149 | 25.202 | 5.83759 | 0.00189097 | 0.000115932 | 2.57626e-06 | 2(Loss) | true |
| Glaze | 883.86 | 0.0478392 | 849.82ms | 1213 | 320 | 125.451 | 1308.81 | 0.0977983 | 5.91773 | 21.6867 | 3.00165 | 0.00086047 | 8.75927e-05 | 1.0305e-05 | 3(Loss) | true |
| simdjson (ondemand) | 378.291 | 0.0798308 | 1029.14ms | 1213 | 1280 | 7628.16 | 3057.98 | 0.0234074 | 13.7878 | 57.2605 | 11.4946 | 0.0075085 | 0.000280168 | 0.000108847 | 4(Loss) | true |
