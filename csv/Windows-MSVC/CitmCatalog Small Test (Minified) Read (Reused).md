
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1109.64 | 0.135048 | 351.473ms | 3223 | 160 | 2238.99 | 2770 | 0.498866 | 2.20797 | 1(Win) | true |
| Jsonifier (two-stage) | 929.31 | 0.127517 | 395.007ms | 3223 | 40 | 711.538 | 3307.5 | 0.0252016 | 2.63505 | 2(Loss) | true |
| Glaze | 589.472 | 0.165527 | 593.385ms | 3223 | 4890 | 364283 | 5214.31 | 0.152246 | 4.17862 | 3(Loss) | true |
| simdjson (ondemand) | 530.633 | 0.179021 | 683.539ms | 3223 | 40 | 4301.28 | 5792.5 | 0.186674 | 4.64314 | 4(Loss) | true |
