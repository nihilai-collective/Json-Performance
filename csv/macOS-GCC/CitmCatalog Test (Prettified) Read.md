
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1331.8 | 1.10907 | 5252.7ms | 1151920 | 30 | 2.51075e+09 | 824866 | 0.738322 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 1288.61 | 1.61983 | 5107.27ms | 1151920 | 320 | 6.10224e+10 | 852510 | 1.12208 | 1(Tie) | true |
