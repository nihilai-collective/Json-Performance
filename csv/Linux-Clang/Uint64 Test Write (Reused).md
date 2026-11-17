
----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4502.96 | 0.124777 | 825.893ms | 3873 | 2560 | 2681.67 | 820.256 | 0.145275 | 1.18671 | 5.12962 | 0.557708 | 0.00662066 | 6.47512e-05 | 1.89614e-05 | 1(Win) | true |
| Glaze | 2226.07 | 0.0690954 | 917.748ms | 3873 | 2560 | 3364.76 | 1659.24 | 0.03556 | 2.36848 | 8.51175 | 1.0457 | 0.00427731 | 4.61932e-05 | 6.65666e-06 | 2(Loss) | true |
