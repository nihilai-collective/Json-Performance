
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1787.94 | 0.206114 | 269.822ms | 4215 | 2560 | 54972.7 | 2248.25 | 0.156335 | 1.36806 | 1(Win) | true |
| Glaze | 1203.31 | 0.0969405 | 373.226ms | 4215 | 40 | 419.481 | 3340.57 | 0.0546015 | 2.04065 | 2(Loss) | true |
| simdjson (reflection) | 1159.46 | 0.35212 | 383.054ms | 4215 | 1280 | 190754 | 3466.9 | 0.017664 | 2.1184 | 3(Loss) | true |
| simdjson (ondemand) | 811.736 | 0.121916 | 534.803ms | 4215 | 40 | 1457.97 | 4952.02 | 0.0405394 | 3.03358 | 4(Loss) | true |
