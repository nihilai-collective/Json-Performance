
----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 797.178 | 0.067012 | 1377.92ms | 5092 | 80 | 1333.1 | 6091.62 | 0.232565 | 6.5066 | 29.2492 | 5.90809 | 0.00650285 | 2.9458e-05 | 2.45483e-06 | 1(Win) | true |
| simdjson (ondemand) | 472.592 | 0.0501465 | 1795.16ms | 5092 | 40 | 1062.05 | 10275.5 | 0.045638 | 10.9452 | 52.1007 | 10.5703 | 0.0171053 | 0.000103103 | 5.40063e-05 | 2(Loss) | true |
