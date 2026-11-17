
----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5464.44 | 0.0906526 | 809.081ms | 3862 | 2560 | 955.727 | 674.011 | 0.116008 | 1.0003 | 5.21647 | 0.592439 | 0.000268036 | 2.62979e-05 | 5.76531e-06 | 1(Win) | true |
| simdjson (reflection) | 3985.7 | 0.0523291 | 816.433ms | 3862 | 40 | 9.35321 | 924.075 | 0.229432 | 1.32727 | 6.79208 | 0.533661 | 0.000517866 | 1.29467e-05 | 0 | 2(Loss) | true |
| Glaze | 2742.1 | 0.0700043 | 884.784ms | 3862 | 160 | 141.458 | 1343.16 | 0.0530746 | 1.93562 | 8.25065 | 0.995857 | 0.00469478 | 3.23666e-05 | 0 | 3(Loss) | true |
