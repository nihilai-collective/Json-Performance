
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 885.094 | 0.0537683 | 845.781ms | 1213 | 4890 | 2414.93 | 1306.99 | 0.0104433 | 5.96425 | 30.0264 | 5.98351 | 0.00170849 | 0.000166061 | 2.8323e-05 | 1(Win) | true |
| simdjson (ondemand) | 376.351 | 0.0713994 | 1024.3ms | 1213 | 640 | 3082.5 | 3073.74 | 0.0234289 | 13.9047 | 58.7205 | 11.8104 | 0.00347666 | 0.000247321 | 0.000113355 | 2(Loss) | true |
