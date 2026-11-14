
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2644.28 | 0.0690522 | 8290.87ms | 7351818 | 160 | 5.36352e+08 | 2.65147e+06 | 0.149365 | 1.89097 | 8.14826 | 1.50512 | 0.0107143 | 0.0614255 | 0.000182436 | 1(Win) | true |
| Jsonifier | 2608.01 | 0.0714895 | 8374.71ms | 7351818 | 160 | 5.90983e+08 | 2.68835e+06 | 0.0101051 | 1.92948 | 8.62411 | 1.96535 | 0.00768858 | 0.0346312 | 0.000242375 | 2(Loss) | true |
| simdjson (reflection) | 2269.95 | 0.035681 | 9625.87ms | 7351818 | 40 | 4.8584e+07 | 3.08872e+06 | 0.0217526 | 2.22446 | 9.71204 | 1.6637 | 0.00904363 | 0.0586496 | 0.000173243 | 3(Loss) | true |
| Glaze | 2059.15 | 0.13201 | 5144.02ms | 7351818 | 80 | 1.61628e+09 | 3.40492e+06 | 0.164582 | 2.44847 | 11.2347 | 2.23762 | 0.00904362 | 0.0338939 | 0.000412697 | 4(Loss) | true |
| simdjson (ondemand) | 1936.39 | 0.0867142 | 5470.56ms | 7351818 | 40 | 3.94316e+08 | 3.62078e+06 | 0.11564 | 2.60174 | 10.3588 | 1.86883 | 0.0103692 | 0.0617506 | 0.000167448 | 5(Loss) | true |
