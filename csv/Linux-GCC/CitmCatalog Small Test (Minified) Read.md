
----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1264.69 | 0.0647927 | 1108.69ms | 5092 | 160 | 990.327 | 3839.75 | 0.0205049 | 4.11559 | 16.7123 | 3.1632 | 0.001943 | 5.52337e-05 | 1.35016e-05 | 1(Win) | true |
| simdjson (ondemand) | 1131.81 | 0.0775361 | 1152.11ms | 5092 | 160 | 1770.74 | 4290.56 | 0.122358 | 4.59517 | 17.7518 | 3.13668 | 0.00220812 | 4.4187e-05 | 1.22742e-06 | 2(Loss) | true |
