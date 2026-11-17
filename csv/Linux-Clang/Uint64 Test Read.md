
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1542.8 | 0.0388889 | 956.131ms | 3873 | 4890 | 4238.74 | 2394.08 | 0.000496999 | 3.39026 | 17.071 | 2.11645 | 0.000778765 | 7.90962e-05 | 3.28423e-05 | 1(Win) | true |
| simdjson (ondemand) | 732.639 | 0.022525 | 1223.68ms | 3873 | 4890 | 6305.99 | 5041.47 | 0.0436563 | 7.05388 | 27.912 | 3.56649 | 0.0151832 | 8.88644e-05 | 4.07625e-05 | 2(Loss) | true |
