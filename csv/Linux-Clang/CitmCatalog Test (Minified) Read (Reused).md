
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2443.35 | 0.114418 | 5882.55ms | 500299 | 640 | 3.19489e+07 | 195274 | 0.359784 | 1.0131 | 1(Win) | true |
| Jsonifier (two-stage) | 2039.33 | 0.122694 | 6785.79ms | 500299 | 640 | 5.27361e+07 | 233960 | 0.0151785 | 1.21384 | 2(Loss) | true |
| Glaze | 1649.81 | 0.12718 | 8423.25ms | 500299 | 320 | 4.32893e+07 | 289199 | 0.535563 | 1.50052 | 3(Loss) | true |
| simdjson (ondemand) | 1173.93 | 0.182382 | 5665.59ms | 500299 | 640 | 3.51658e+08 | 406432 | 0.262502 | 2.10879 | 4(Loss) | true |
