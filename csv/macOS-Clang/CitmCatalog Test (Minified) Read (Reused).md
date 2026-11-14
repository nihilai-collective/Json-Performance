
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2651.43 | 0.0820639 | 5524.37ms | 500299 | 1280 | 2.79134e+07 | 179949 | 0.134223 | 1(Win) | true |
| Jsonifier (two-stage) | 1663.28 | 0.114551 | 8312.02ms | 500299 | 320 | 3.45525e+07 | 286857 | 0.0148767 | 2(Loss) | true |
| Glaze | 1422.38 | 0.128333 | 9486.25ms | 500299 | 320 | 5.92995e+07 | 335439 | 0.0334552 | 3(Loss) | true |
| simdjson (ondemand) | 916.209 | 0.123699 | 7051.64ms | 500299 | 640 | 2.65571e+08 | 520757 | 0.155272 | 4(Loss) | true |
