
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2678.28 | 0.195238 | 36.3397ms | 905 | 40 | 15.8333 | 322.25 | 0.0878462 | 0.846022 | 1(Win) | true |
| Glaze | 2239.37 | 0.046424 | 41.676ms | 905 | 1280 | 40.9769 | 385.409 | 0.0263588 | 1.0274 | 2(Loss) | true |
| simdjson (reflection) | 1157.77 | 0.125827 | 78.0373ms | 905 | 30 | 26.3954 | 745.467 | 0.0446947 | 2.06361 | 3(Loss) | true |
| simdjson (ondemand) | 468.714 | 0.171429 | 189.277ms | 905 | 30 | 298.93 | 1841.37 | 0.0325951 | 5.2018 | 4(Loss) | true |
