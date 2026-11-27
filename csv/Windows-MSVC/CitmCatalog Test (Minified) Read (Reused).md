
----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 799.037 | 0.0706064 | 8089.35ms | 500299 | 640 | 1.13761e+08 | 597122 | 0.119596 | 3.80348 | 1(Win) | true |
| simdjson (ondemand) | 691.978 | 0.0493056 | 9290.14ms | 500299 | 640 | 7.39686e+07 | 689505 | 0.0636827 | 4.39206 | 2(Loss) | true |
