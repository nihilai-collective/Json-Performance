
----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 740.698 | 0.101688 | 1435.08ms | 5092 | 40 | 1777.86 | 6556.12 | 0.0717643 | 6.99976 | 30.075 | 6.10112 | 0.00760998 | 5.89159e-05 | 4.90966e-06 | 1(Win) | true |
| simdjson (ondemand) | 471.684 | 0.0554119 | 1793.64ms | 5092 | 640 | 20828.7 | 10295.3 | 0.00840729 | 10.9541 | 52.1233 | 10.5396 | 0.0180961 | 5.30857e-05 | 9.81932e-06 | 2(Loss) | true |
