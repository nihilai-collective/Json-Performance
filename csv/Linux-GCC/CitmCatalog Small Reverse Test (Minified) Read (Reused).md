
----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 732.423 | 0.0511501 | 1438.55ms | 5092 | 4890 | 56241.1 | 6630.19 | 0.0346185 | 7.06231 | 30.1486 | 6.11614 | 0.00787783 | 8.52213e-05 | 3.34138e-05 | 1(Win) | true |
| simdjson (ondemand) | 475.729 | 0.041801 | 1780.56ms | 5092 | 1280 | 23304.6 | 10207.7 | 0.000397981 | 10.8629 | 52.1363 | 10.5393 | 0.0166255 | 4.38801e-05 | 8.89876e-06 | 2(Loss) | true |
