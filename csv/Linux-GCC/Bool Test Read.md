
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2796.52 | 0.223565 | 33.9162ms | 905 | 80 | 38.0854 | 308.625 | 0.121655 | 0.814613 | 1(Win) | true |
| Glaze | 2372.63 | 0.206569 | 40.3743ms | 905 | 80 | 45.1707 | 363.762 | 0.359515 | 0.969157 | 2(Loss) | true |
| simdjson (reflection) | 1209.57 | 0.0894119 | 74.3371ms | 905 | 640 | 260.499 | 713.539 | 0.152422 | 1.97424 | 3(Loss) | true |
| simdjson (ondemand) | 528.279 | 0.0549549 | 172.658ms | 905 | 40 | 32.2436 | 1633.75 | 0.109275 | 4.60956 | 4(Loss) | true |
