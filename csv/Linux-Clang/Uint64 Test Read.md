
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2217.7 | 0.173982 | 757.745ms | 1213 | 320 | 263.558 | 521.625 | 0.184861 | 2.49587 | 11.1674 | 2.70074 | 0.000896538 | 9.78978e-05 | 5.15251e-06 | 1(Win) | true |
| simdjson (stage-1) | 1112.36 | 0.136335 | 811.333ms | 1213 | 1280 | 2573.09 | 1039.96 | 0.250359 | 4.87994 | 24.676 | 5.50206 | 0.00247192 | 0.000103694 | 4.50845e-06 | 2(Loss) | true |
