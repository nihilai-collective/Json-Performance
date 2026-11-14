
----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5185.56 | 0.0815401 | 830.524ms | 3862 | 4890 | 1640.15 | 710.258 | 0.152046 | 1.03517 | 5.21647 | 0.592439 | 0.000996072 | 5.09394e-05 | 1.84801e-05 | 1(Win) | true |
| simdjson (reflection) | 4001.51 | 0.0708696 | 835.228ms | 3862 | 40 | 17.0199 | 920.425 | 0.00996016 | 1.32092 | 6.79208 | 0.533661 | 0.000258933 | 3.884e-05 | 6.47333e-06 | 2(Loss) | true |
| Glaze | 2726.53 | 0.200567 | 897.821ms | 3862 | 30 | 220.213 | 1350.83 | 0.135535 | 1.91548 | 8.25065 | 0.995857 | 0.00495426 | 1.72622e-05 | 0 | 3(Loss) | true |
