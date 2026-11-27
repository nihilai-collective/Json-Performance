
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3077.72 | 0.470847 | 5123.24ms | 1151920 | 80 | 2.25963e+08 | 356939 | 0.144424 | 0.987371 | 1(Win) | true |
| Jsonifier | 3046.11 | 0.149571 | 5131.55ms | 1151920 | 640 | 1.86222e+08 | 360643 | 0.0926737 | 0.99768 | 2(Loss) | true |
| Glaze | 1679.94 | 0.350072 | 9094.78ms | 1151920 | 80 | 4.19241e+08 | 653926 | 0.353541 | 1.80914 | 3(Loss) | true |
| simdjson (ondemand) | 1457.03 | 0.161495 | 5031.6ms | 1151920 | 160 | 2.37217e+08 | 753968 | 0.6933 | 2.08583 | 4(Loss) | true |
