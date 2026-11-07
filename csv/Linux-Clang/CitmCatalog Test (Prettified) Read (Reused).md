
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4477.94 | 0.180684 | 7030.95ms | 1151920 | 1280 | 2.51501e+08 | 245326 | 0.159636 | 0.552805 | 1(Win) | true |
| Jsonifier | 3635.21 | 0.116735 | 8509.18ms | 1151920 | 320 | 3.98232e+07 | 302199 | 0.120643 | 0.680993 | 2(Loss) | true |
| Glaze | 2746.71 | 0.0398178 | 5569.57ms | 1151920 | 640 | 1.62313e+07 | 399953 | 0.00747292 | 0.901308 | 3(Loss) | true |
| simdjson (ondemand) | 2725.11 | 0.144904 | 5471.15ms | 1151920 | 40 | 1.36489e+07 | 403124 | 0.00552177 | 0.908448 | 4(Loss) | true |
