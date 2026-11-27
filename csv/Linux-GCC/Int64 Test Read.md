
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 895.609 | 0.138217 | 862.323ms | 1313 | 1280 | 4779.96 | 1398.13 | 0.344781 | 5.92577 | 29.035 | 5.7936 | 0.000869907 | 0.000234435 | 9.63919e-05 | 1(Win) | true |
| simdjson (ondemand) | 399.557 | 0.0430505 | 1036.35ms | 1313 | 2560 | 4659.79 | 3133.9 | 0.126437 | 13.0329 | 55.2513 | 10.936 | 0.00247495 | 0.000211229 | 9.93669e-05 | 2(Loss) | true |
