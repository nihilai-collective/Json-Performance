
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3901.27 | 0.0475403 | 7183.35ms | 1151920 | 1280 | 2.29386e+07 | 281589 | 0.101928 | 0.634514 | 1(Win) | true |
| Jsonifier | 3186.42 | 0.102893 | 8734.41ms | 1151920 | 160 | 2.0134e+07 | 344762 | 0.161282 | 0.776883 | 2(Loss) | true |
| Glaze | 2486.56 | 0.0765968 | 5670.04ms | 1151920 | 160 | 1.83226e+07 | 441798 | 0.0272194 | 0.995586 | 3(Loss) | true |
| simdjson (ondemand) | 2444.28 | 0.107248 | 5716.85ms | 1151920 | 80 | 1.85872e+07 | 449440 | 0.065297 | 1.01281 | 4(Loss) | true |
