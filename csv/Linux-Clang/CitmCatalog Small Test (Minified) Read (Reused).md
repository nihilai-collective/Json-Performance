
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2240.97 | 0.0837851 | 189.301ms | 3223 | 160 | 211.3 | 1371.59 | 0.844915 | 1.08402 | 1(Win) | true |
| Jsonifier (two-stage) | 1950.15 | 0.196161 | 175.223ms | 3223 | 4890 | 46743 | 1576.13 | 0.0406704 | 1.24858 | 2(Loss) | true |
| Glaze | 1574.59 | 0.0887636 | 211.55ms | 3223 | 80 | 240.186 | 1952.06 | 0.021136 | 1.55116 | 3(Loss) | true |
| simdjson (ondemand) | 1240.38 | 0.0578815 | 274.984ms | 3223 | 80 | 164.582 | 2478.03 | 0.223468 | 1.97477 | 4(Loss) | true |
