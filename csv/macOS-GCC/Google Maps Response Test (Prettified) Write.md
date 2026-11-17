
----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16787.7 | 2.31012 | 191.772ms | 31235 | 160 | 268839 | 1774.4 | 0.805009 | 1(Win) | true |
| Glaze | 2581.51 | 0.456541 | 1236.12ms | 31235 | 1280 | 3.55226e+06 | 11539 | 0.332151 | 2(Loss) | true |
| simdjson (reflection) | 282.226 | 0.432492 | 5201.54ms | 31235 | 640 | 1.3336e+08 | 105547 | 0.125285 | 3(Loss) | true |
