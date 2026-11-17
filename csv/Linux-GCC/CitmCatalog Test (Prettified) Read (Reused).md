
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4222.49 | 0.0682313 | 7770.73ms | 1151920 | 1280 | 4.03352e+07 | 260168 | 0.0201098 | 1.1871 | 5.69546 | 0.829863 | 0.00441949 | 0.0471265 | 6.94533e-05 | 1(Win) | true |
| Jsonifier | 3856.23 | 0.0899665 | 8326.08ms | 1151920 | 160 | 1.05099e+07 | 284878 | 0.0960762 | 1.30168 | 6.18658 | 1.26739 | 0.00335547 | 0.0121718 | 2.13068e-05 | 2(Loss) | true |
| simdjson (ondemand) | 3597.02 | 0.0483969 | 8816.42ms | 1151920 | 320 | 6.99107e+06 | 305407 | 0.119225 | 1.40478 | 6.45925 | 0.968431 | 0.00409874 | 0.0362714 | 1.31492e-05 | 3(Loss) | true |
| simdjson (reflection) | 3493.29 | 0.0417668 | 9073.57ms | 1151920 | 1280 | 2.20825e+07 | 314477 | 0.136737 | 1.44512 | 6.47483 | 0.984222 | 0.00483811 | 0.0348663 | 2.18819e-05 | 4(Loss) | true |
| Glaze | 2854.36 | 0.0833573 | 5406.27ms | 1151920 | 160 | 1.64678e+07 | 384869 | 0.00607312 | 1.76125 | 7.99431 | 1.49585 | 0.00541696 | 0.00925718 | 3.22234e-05 | 5(Loss) | true |
