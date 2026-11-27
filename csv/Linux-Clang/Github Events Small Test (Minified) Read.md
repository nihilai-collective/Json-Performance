
----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1272.7 | 0.100292 | 851.035ms | 1691 | 160 | 258.395 | 1267.12 | 0.107149 | 4.17987 | 14.5405 | 2.83619 | 0.000887049 | 0.000136753 | 5.54406e-05 | 1(Win) | true |
| simdjson (ondemand) | 1215.27 | 0.167183 | 852.801ms | 1691 | 40 | 196.872 | 1327 | 0.105613 | 4.4479 | 16.7451 | 2.89651 | 0.00147842 | 0.00017741 | 0 | 2(Loss) | true |
