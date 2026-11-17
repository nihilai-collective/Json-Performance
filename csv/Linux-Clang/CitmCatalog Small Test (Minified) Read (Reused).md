
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2171.68 | 0.204627 | 162.939ms | 3223 | 4890 | 41017.2 | 1415.35 | 0.566043 | 1.11783 | 1(Win) | true |
| Jsonifier (two-stage) | 1798.4 | 0.227447 | 189.82ms | 3223 | 4890 | 73895.4 | 1709.13 | 0.106436 | 1.35324 | 2(Loss) | true |
| Glaze | 1513.61 | 0.13668 | 228.481ms | 3223 | 30 | 231.114 | 2030.7 | 0.292962 | 1.61577 | 3(Loss) | true |
| simdjson (ondemand) | 1161.1 | 0.14393 | 296.102ms | 3223 | 40 | 580.692 | 2647.22 | 0.0795798 | 2.10791 | 4(Loss) | true |
