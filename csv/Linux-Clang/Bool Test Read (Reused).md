
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 669.294 | 0.117768 | 842.953ms | 905 | 2560 | 5904.21 | 1289.53 | 0.028028 | 7.9428 | 36.6829 | 6.58011 | 0.00589693 | 0.000175242 | 4.74793e-05 | 1(Win) | true |
| simdjson (ondemand) | 513.06 | 0.144944 | 887.069ms | 905 | 80 | 475.612 | 1682.21 | 0.0825487 | 10.2795 | 49.8851 | 9.69615 | 0.040221 | 8.28729e-05 | 2.76243e-05 | 2(Loss) | true |
