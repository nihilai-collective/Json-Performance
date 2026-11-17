
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 560.593 | 0.507082 | 870.713ms | 905 | 80 | 4875.82 | 1539.58 | 0.0178653 | 9.56497 | 49.3702 | 6.37018 | 0.00312155 | 2.76243e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 288.89 | 0.0355395 | 1022.35ms | 905 | 320 | 360.749 | 2987.56 | 0.0244825 | 18.072 | 88.9459 | 9.47735 | 0.0219544 | 0.000107044 | 3.45304e-05 | 2(Loss) | true |
