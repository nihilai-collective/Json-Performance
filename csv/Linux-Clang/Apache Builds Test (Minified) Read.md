
----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1442.72 | 0.0343563 | 6996.46ms | 94653 | 1280 | 591467 | 62568.2 | 0.121536 | 3.51045 | 15.1163 | 2.92863 | 0.00873996 | 2.97221e-05 | 2.2013e-05 | 1(Win) | true |
| simdjson (ondemand) | 1265.54 | 0.0204528 | 7893.16ms | 94653 | 4890 | 1.04071e+06 | 71327.5 | 0.0911274 | 4.03261 | 16.5855 | 3.09583 | 0.0110691 | 4.15704e-05 | 2.76113e-05 | 2(Loss) | true |
