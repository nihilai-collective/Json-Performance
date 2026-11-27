
----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 771.561 | 0.099353 | 8375.88ms | 4219119 | 40 | 1.0738e+09 | 5.21497e+06 | 0.109103 | 6.58214 | 25.9953 | 4.76856 | 0.0218879 | 0.0535487 | 0.0044414 | 1(Win) | true |
| simdjson (ondemand) | 303.241 | 0.080399 | 9566.13ms | 4219119 | 30 | 3.41421e+09 | 1.32689e+07 | 0.174243 | 16.6942 | 64.3369 | 13.2857 | 0.0890498 | 0.0552536 | 0.0171624 | 2(Loss) | true |
