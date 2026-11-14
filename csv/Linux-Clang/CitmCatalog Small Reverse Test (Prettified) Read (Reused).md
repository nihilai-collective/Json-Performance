
----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1274.31 | 0.0178234 | 1492.91ms | 9739 | 4890 | 8252.1 | 7288.5 | 0.0049833 | 4.06446 | 17.1969 | 3.34764 | 0.00370765 | 2.30767e-05 | 4.36757e-06 | 1(Win) | true |
| simdjson (ondemand) | 891.323 | 0.0322948 | 1805.13ms | 9739 | 1280 | 14495.5 | 10420.3 | 0.0618602 | 5.79981 | 28.9591 | 5.52192 | 0.00643346 | 3.03227e-05 | 1.05889e-05 | 2(Loss) | true |
