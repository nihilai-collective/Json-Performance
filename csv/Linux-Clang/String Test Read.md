
----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6862.01 | 0.108718 | 846.198ms | 9578 | 1280 | 2680.75 | 1331.14 | 0.265514 | 0.767823 | 3.59626 | 0.338066 | 0.0010191 | 1.08484e-05 | 4.56776e-06 | 1(Win) | true |
| simdjson (stage-1) | 4382.16 | 0.0523256 | 927.499ms | 9578 | 40 | 47.584 | 2084.43 | 0.0818899 | 1.22195 | 5.95218 | 0.484861 | 0.000944874 | 1.56609e-05 | 0 | 2(Loss) | true |
