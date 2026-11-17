
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2479.54 | 0.498142 | 5490.59ms | 1151920 | 320 | 1.55868e+09 | 443048 | 0.291598 | 1(Win) | true |
| Jsonifier (two-stage) | 2216.88 | 1.37888 | 5852.51ms | 1151920 | 30 | 1.40067e+09 | 495542 | 0.654228 | 2(Loss) | true |
| Glaze | 1788.96 | 1.14637 | 7768.9ms | 1151920 | 80 | 3.96441e+09 | 614074 | 0.683065 | 3(Loss) | true |
| simdjson (ondemand) | 1545.4 | 0.845602 | 9198.97ms | 1151920 | 80 | 2.89057e+09 | 710855 | 0.0198753 | 4(Loss) | true |
