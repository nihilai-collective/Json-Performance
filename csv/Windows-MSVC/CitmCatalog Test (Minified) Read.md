
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1392.94 | 0.0779758 | 8785.33ms | 500299 | 1280 | 9.13116e+07 | 342530 | 0.0578067 | 1.77714 | 1(Win) | true |
| Jsonifier (two-stage) | 1189.94 | 0.124321 | 5178.47ms | 500299 | 320 | 7.95155e+07 | 400964 | 0.874159 | 2.08041 | 2(Loss) | true |
| Glaze | 774.453 | 0.302372 | 7983.81ms | 500299 | 30 | 1.04105e+08 | 616077 | 0.257959 | 3.19664 | 3(Loss) | true |
| simdjson (ondemand) | 600.592 | 0.21662 | 5144.48ms | 500299 | 30 | 8.88423e+07 | 794420 | 0.14204 | 4.12205 | 4(Loss) | true |
