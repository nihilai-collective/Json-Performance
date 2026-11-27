
----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2371.63 | 0.224253 | 780.283ms | 1213 | 160 | 191.437 | 487.769 | 0.175237 | 2.36032 | 12.6216 | 1.46414 | 0.00108718 | 0.000139118 | 4.63726e-05 | 1(Win) | true |
| Glaze | 955.411 | 0.0935624 | 866.195ms | 1213 | 4890 | 6275.56 | 1210.8 | 0.495591 | 5.57216 | 21.9143 | 2.9695 | 0.00320505 | 0.000226247 | 7.51909e-05 | 2(Loss) | true |
