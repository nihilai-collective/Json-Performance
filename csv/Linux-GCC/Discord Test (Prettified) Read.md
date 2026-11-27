
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2609.1 | 0.249202 | 3140.11ms | 83958 | 4890 | 2.85993e+07 | 30688.2 | 0.151941 | 0.94803 | 1(Win) | true |
| Jsonifier (two-stage) | 2422.85 | 0.085442 | 3262.51ms | 83958 | 4890 | 3.89874e+06 | 33047.3 | 0.644282 | 1.02092 | 2(Loss) | true |
| simdjson (reflection) | 2300.46 | 0.109038 | 3465.05ms | 83958 | 2560 | 3.68716e+06 | 34805.4 | 0.234744 | 1.07536 | 3(Loss) | true |
| simdjson (ondemand) | 2001.28 | 0.141084 | 3998.84ms | 83958 | 1280 | 4.07824e+06 | 40008.7 | 0.0749333 | 1.23627 | 4(Loss) | true |
| Glaze | 1848.98 | 0.110101 | 4361.77ms | 83958 | 4890 | 1.1116e+07 | 43304.3 | 0.309342 | 1.33816 | 5(Loss) | true |
