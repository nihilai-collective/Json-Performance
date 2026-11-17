
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1075.64 | 0.0879916 | 350.728ms | 3223 | 4890 | 30915.6 | 2857.55 | 0.0645336 | 2.80315 | 1(Win) | true |
| Jsonifier (two-stage) | 864.193 | 0.112981 | 421.197ms | 3223 | 2560 | 41338.2 | 3556.72 | 0.0857388 | 3.4953 | 2(Loss) | true |
| Glaze | 745.979 | 0.064723 | 471.397ms | 3223 | 4890 | 34777.1 | 4120.35 | 0.0872006 | 4.05372 | 3(Loss) | true |
| simdjson (ondemand) | 595.159 | 0.0921093 | 578.02ms | 3223 | 2560 | 57929.8 | 5164.49 | 0.0461171 | 5.08673 | 4(Loss) | true |
