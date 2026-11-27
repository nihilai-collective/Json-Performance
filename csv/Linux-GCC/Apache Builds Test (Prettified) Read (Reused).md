
----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3390.57 | 0.0391569 | 5485.16ms | 124597 | 2560 | 482087 | 35045.7 | 0.0462914 | 1.50115 | 7.60636 | 1.35953 | 0.00474792 | 1.3343e-05 | 4.90958e-06 | 1(Win) | true |
| simdjson (ondemand) | 2531.35 | 0.0566166 | 6674.17ms | 124597 | 320 | 226021 | 46941.4 | 0.118232 | 2.00092 | 8.41824 | 1.55112 | 0.00569963 | 1.87103e-05 | 1.40704e-05 | 2(Loss) | true |
| simdjson (reflection) | 2331.02 | 0.0274721 | 7091.99ms | 124597 | 2560 | 502050 | 50975.4 | 0.0424143 | 2.17419 | 8.7865 | 1.45669 | 0.00307387 | 2.3275e-05 | 1.60518e-05 | 3(Loss) | true |
| Jsonifier (two-stage) | 2238.99 | 0.0749905 | 7296.37ms | 124597 | 320 | 506845 | 53070.9 | 0.0606309 | 2.25976 | 10.5819 | 1.67189 | 0.00866298 | 9.27992e-06 | 6.39562e-06 | 4(Loss) | true |
| Glaze | 2193.07 | 0.0669396 | 7378.71ms | 124597 | 80 | 105237 | 54182.1 | 0.113566 | 2.30636 | 10.9245 | 2.09235 | 0.00965332 | 4.41423e-06 | 8.02588e-07 | 5(Loss) | true |
