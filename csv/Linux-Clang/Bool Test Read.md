
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 556.173 | 0.0668298 | 864.13ms | 905 | 4890 | 5259.28 | 1551.81 | 0.0100994 | 9.49675 | 49.3702 | 6.37017 | 0.00123242 | 0.000135353 | 2.73419e-05 | 1(Win) | true |
| simdjson (ondemand) | 287.339 | 0.0582536 | 1015.17ms | 905 | 160 | 489.864 | 3003.69 | 0.149592 | 18.1754 | 88.9459 | 9.47735 | 0.0239572 | 0.000379834 | 0.000172652 | 2(Loss) | true |
