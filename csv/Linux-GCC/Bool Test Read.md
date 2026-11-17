
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2219.15 | 0.247562 | 751.467ms | 905 | 320 | 296.649 | 388.922 | 0.0425675 | 2.56597 | 11.7072 | 1.86961 | 0.00110497 | 4.14365e-05 | 3.45304e-06 | 1(Win) | true |
| Glaze | 1816.24 | 0.0495966 | 769.214ms | 905 | 4890 | 271.622 | 475.199 | 0.0806155 | 3.08096 | 14.032 | 1.94917 | 0.00110949 | 5.73953e-05 | 1.10723e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 615.931 | 0.0677044 | 852.757ms | 905 | 4890 | 4401.25 | 1401.25 | 0.367511 | 8.52582 | 42.8906 | 4.43094 | 0.00848049 | 0.000152753 | 2.44043e-05 | 3(Loss) | true |
| simdjson (ondemand) | 229.482 | 0.122922 | 1099.1ms | 905 | 1280 | 27357 | 3760.97 | 0.021225 | 22.5461 | 105.526 | 9.82431 | 0.0767559 | 0.000154523 | 6.21547e-05 | 4(Loss) | true |
