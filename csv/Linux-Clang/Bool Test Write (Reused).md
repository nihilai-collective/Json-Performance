
----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4587.93 | 0.537821 | 739.841ms | 905 | 320 | 327.56 | 188.119 | 0.301424 | 1.38295 | 5.79779 | 0.272928 | 0.00223412 | 2.41713e-05 | 0 | 1(Win) | true |
| Glaze | 973.16 | 0.116736 | 832.621ms | 905 | 4890 | 5241.4 | 886.879 | 0.27733 | 5.54028 | 24.0597 | 3.14917 | 0.00129637 | 0.00010756 | 2.75678e-05 | 2(Loss) | true |
