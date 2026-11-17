
----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1316.97 | 0.0172713 | 1473.54ms | 9739 | 4890 | 7254.96 | 7052.41 | 0.00887759 | 3.93381 | 17.1964 | 3.34625 | 0.00317313 | 2.77383e-05 | 8.77714e-06 | 1(Win) | true |
| simdjson (ondemand) | 873.203 | 0.0399531 | 1829.96ms | 9739 | 1280 | 23115.9 | 10636.5 | 0.0645011 | 5.91773 | 28.9677 | 5.52511 | 0.00699283 | 2.00547e-05 | 2.80765e-06 | 2(Loss) | true |
