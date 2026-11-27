
----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4351.02 | 0.0217488 | 2921.56ms | 83958 | 2560 | 41006.5 | 18402.3 | 0.0263994 | 1.16423 | 5.90532 | 1.1256 | 0.00166105 | 1.29669e-05 | 7.05338e-06 | 1(Win) | true |
| Glaze | 3293.74 | 0.108093 | 3537.15ms | 83958 | 320 | 220948 | 24309.3 | 0.143707 | 1.54683 | 8.4912 | 1.73109 | 0.00206859 | 4.91317e-06 | 1.6005e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 3220.81 | 0.052859 | 3559.38ms | 83958 | 320 | 55256.1 | 24859.7 | 0.00725267 | 1.57289 | 7.88101 | 1.22448 | 0.00203766 | 8.11418e-06 | 3.7221e-06 | 3(Loss) | true |
| simdjson (reflection) | 2622.62 | 0.0224411 | 4148.68ms | 83958 | 4890 | 229535 | 30530 | 0.160026 | 1.9335 | 8.58703 | 1.34234 | 0.00214452 | 1.15697e-05 | 5.93831e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2333.81 | 0.0274758 | 4548.3ms | 83958 | 4890 | 434513 | 34308 | 0.19507 | 2.17799 | 9.08777 | 1.52848 | 0.00555672 | 1.15259e-05 | 5.61192e-06 | 5(Loss) | true |
