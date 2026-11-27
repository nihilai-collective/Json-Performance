
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4396.34 | 0.164479 | 7235.08ms | 1151920 | 320 | 5.40549e+07 | 249880 | 0.0667203 | 0.563078 | 1(Win) | true |
| Jsonifier (two-stage) | 4232.04 | 0.0677947 | 7535.81ms | 1151920 | 640 | 1.98206e+07 | 259581 | 0.179171 | 0.584935 | 2(Loss) | true |
| Glaze | 2694.76 | 0.110459 | 5636.65ms | 1151920 | 160 | 3.24433e+07 | 407664 | 0.182504 | 0.918681 | 3(Loss) | true |
| simdjson (ondemand) | 2643 | 0.207433 | 5646.46ms | 1151920 | 40 | 2.97347e+07 | 415647 | 0.103466 | 0.93665 | 4(Loss) | true |
