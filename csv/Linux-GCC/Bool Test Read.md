
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2416.46 | 0.123963 | 749.573ms | 905 | 4890 | 958.587 | 357.165 | 0.159371 | 2.35375 | 11.7072 | 1.86961 | 0.00111469 | 0.000113435 | 3.36689e-05 | 1(Win) | true |
| Glaze | 1821.44 | 0.133769 | 769.148ms | 905 | 2560 | 1028.53 | 473.842 | 0.0972644 | 3.07752 | 14.032 | 1.94917 | 0.00111576 | 0.000106181 | 5.52486e-05 | 2(Loss) | true |
| simdjson (reflection) | 1145.27 | 0.0820369 | 787.262ms | 905 | 2560 | 978.462 | 753.603 | 0.218005 | 4.74319 | 23.274 | 5.49061 | 0.0043996 | 9.92749e-05 | 3.79834e-05 | 3(Loss) | true |
| simdjson (ondemand) | 488.42 | 0.0351589 | 918.231ms | 905 | 4890 | 1887.52 | 1767.08 | 0.0820284 | 10.7923 | 50.8133 | 9.59227 | 0.0588609 | 0.000168796 | 2.41783e-05 | 4(Loss) | true |
