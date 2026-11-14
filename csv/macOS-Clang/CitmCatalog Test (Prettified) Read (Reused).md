
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3364.54 | 0.0857535 | 9244.25ms | 1151920 | 1280 | 1.00348e+08 | 326510 | 0.204279 | 1(Win) | true |
| Jsonifier (two-stage) | 3206.74 | 0.0867463 | 9855.51ms | 1151920 | 640 | 5.65196e+07 | 342577 | 0.514263 | 2(Loss) | true |
| Glaze | 2146.85 | 0.175183 | 6984.89ms | 1151920 | 160 | 1.28573e+08 | 511707 | 0.139489 | 3(Loss) | true |
| simdjson (ondemand) | 1896.69 | 0.124684 | 7762.15ms | 1151920 | 320 | 1.66889e+08 | 579197 | 0.00496941 | 4(Loss) | true |
