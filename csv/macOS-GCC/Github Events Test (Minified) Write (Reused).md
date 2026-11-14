
----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16024.2 | 0.240699 | 354.964ms | 58581 | 4890 | 344362 | 3486.42 | 0.336849 | 1(Win) | true |
| simdjson (reflection) | 11463.8 | 0.228219 | 493.134ms | 58581 | 4890 | 604884 | 4873.37 | 0.174124 | 2(Loss) | true |
| Glaze | 4362.97 | 0.128847 | 1293.52ms | 58581 | 4890 | 1.33108e+06 | 12804.9 | 0.0395999 | 3(Loss) | true |
