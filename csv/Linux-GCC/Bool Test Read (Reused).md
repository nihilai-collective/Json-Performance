
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2484.38 | 0.15109 | 37.6298ms | 905 | 80 | 22.0405 | 347.4 | 0.0431593 | 0.925594 | 1(Win) | true |
| Jsonifier | 2458.66 | 0.0659354 | 37.6673ms | 905 | 320 | 17.143 | 351.034 | 0.0365126 | 0.934413 | 2(Loss) | true |
| simdjson (reflection) | 1289.52 | 0.127575 | 70.7377ms | 905 | 30 | 21.8724 | 669.3 | 0.044843 | 1.84052 | 3(Loss) | true |
| simdjson (ondemand) | 521.661 | 0.052878 | 166.577ms | 905 | 40 | 30.6147 | 1654.47 | 0.140331 | 4.66414 | 4(Loss) | true |
