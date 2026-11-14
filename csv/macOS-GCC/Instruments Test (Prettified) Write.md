
----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12863 | 0.926825 | 1370.46ms | 213963 | 30 | 648505 | 15863.5 | 0.215633 | 1(Win) | true |
| Glaze | 1882.39 | 0.957324 | 5261.08ms | 213963 | 80 | 8.61522e+07 | 108400 | 2.38469 | 2(Loss) | true |
| simdjson (reflection) | 309.978 | 0.269389 | 8653.98ms | 213963 | 640 | 2.01259e+09 | 658277 | 2.06133 | 3(Loss) | true |
