
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 3427.61 | 0.224869 | 829.915ms | 4215 | 1280 | 8901.87 | 1172.75 | 0.0899182 | 1.55909 | 7.30819 | 1.00261 | 0.00166111 | 5.06005e-05 | 1.42719e-05 | 1(Win) | true |
| simdjson (stage-1) | 3278.65 | 0.104166 | 833.802ms | 4215 | 30 | 48.9299 | 1226.03 | 0.0135958 | 1.62108 | 8.30558 | 0.879004 | 0.00127323 | 2.37248e-05 | 0 | 2(Loss) | true |
