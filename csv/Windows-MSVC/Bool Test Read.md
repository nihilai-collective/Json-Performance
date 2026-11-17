
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 451.576 | 0.186007 | 205.637ms | 905 | 80 | 1011.08 | 1911.25 | 0.065445 | 5.40054 | 1(Win) | true |
| Jsonifier | 436.103 | 0.143957 | 208.294ms | 905 | 640 | 5194.74 | 1979.06 | 0.252008 | 5.60386 | 2(Loss) | true |
| Jsonifier (two-stage) | 157.209 | 0.15707 | 564.436ms | 905 | 40 | 2974.36 | 5490 | 0 | 15.6294 | 3(Loss) | true |
| simdjson (ondemand) | 68.0961 | 0.448526 | 1353.14ms | 905 | 320 | 1.03414e+06 | 12674.4 | 0.255767 | 36.247 | 4(Loss) | true |
