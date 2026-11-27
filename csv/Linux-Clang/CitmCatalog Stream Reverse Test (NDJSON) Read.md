
----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 802.641 | 0.453179 | 8650.34ms | 4525120 | 80 | 4.7495e+10 | 5.37662e+06 | 1.69541 | 6.3197 | 31.3195 | 6.31957 | 0.0162508 | 0.0778547 | 0.00910059 | 1(Win) | true |
| simdjson (ondemand) | 599.852 | 0.680561 | 5318.22ms | 4525120 | 30 | 7.19163e+10 | 7.19426e+06 | 0.789384 | 8.47485 | 42.9346 | 8.0864 | 0.0247395 | 0.0779742 | 0.0085729 | 2(Loss) | true |
