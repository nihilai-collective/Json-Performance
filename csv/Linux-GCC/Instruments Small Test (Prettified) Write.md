
----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20767.3 | 0.125437 | 769.676ms | 9249 | 4890 | 1387.99 | 424.731 | 0.121707 | 0.267382 | 0.719537 | 0.162937 | 0.000111547 | 2.53606e-05 | 1.15416e-05 | 1(Win) | true |
| Glaze | 3253.65 | 0.17892 | 1004.15ms | 9249 | 4890 | 115047 | 2710.96 | 0.00270698 | 1.58278 | 3.79436 | 0.624933 | 0.00038209 | 3.97766e-05 | 2.18451e-05 | 2(Loss) | true |
| simdjson (reflection) | 508.907 | 0.300055 | 2461.11ms | 9249 | 320 | 865494 | 17332.3 | 0.00191113 | 9.94147 | 40.8158 | 8.29486 | 0.0147982 | 8.85231e-05 | 4.89918e-05 | 3(Loss) | true |
