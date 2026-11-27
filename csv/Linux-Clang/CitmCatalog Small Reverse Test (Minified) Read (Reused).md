
----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 769.506 | 0.0632689 | 1398.72ms | 5092 | 640 | 10202.7 | 6310.68 | 0.101295 | 6.7334 | 29.9768 | 6.07973 | 0.00647247 | 3.31402e-05 | 6.13708e-06 | 1(Win) | true |
| simdjson (ondemand) | 461.446 | 0.0467503 | 1817.1ms | 5092 | 1280 | 30982.3 | 10523.7 | 0.0813336 | 11.1378 | 54.4509 | 10.5414 | 0.0141983 | 8.86808e-05 | 4.11184e-05 | 2(Loss) | true |
