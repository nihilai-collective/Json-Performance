
----
### Validate Test Read Results [(Here is the data we used for this test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3343.85 | 0.0626177 | 9596.2ms | 631514 | 2560 | 3.25616e+07 | 180109 | 0.238201 | 1.50851 | 6.95146 | 1.21163 | 0.00769683 | 2.43283e-05 | 1.10245e-05 | 1(Win) | true |
| Glaze | 2592.94 | 0.0598557 | 6101.23ms | 631514 | 320 | 6.18503e+06 | 232268 | 0.252287 | 1.95487 | 8.44884 | 1.51664 | 0.00370023 | 6.03708e-06 | 4.56245e-06 | 2(Loss) | true |
