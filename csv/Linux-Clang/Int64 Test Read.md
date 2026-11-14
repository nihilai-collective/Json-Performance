
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1557.77 | 0.0330724 | 951.414ms | 3862 | 4890 | 2989.91 | 2364.34 | 0.0480162 | 3.36069 | 16.9444 | 2.10177 | 0.00117685 | 3.56894e-05 | 2.22397e-06 | 1(Win) | true |
| simdjson (ondemand) | 795.483 | 0.0247546 | 1177.35ms | 3862 | 2560 | 3362.9 | 4630 | 0.0126368 | 6.52939 | 28.2372 | 3.48887 | 0.0138927 | 4.17732e-05 | 1.41604e-06 | 2(Loss) | true |
