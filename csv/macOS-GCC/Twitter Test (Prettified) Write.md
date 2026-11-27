
----
### Twitter Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16748.5 | 0.114915 | 4165.33ms | 716365 | 80 | 175775 | 40790.4 | 0.0235294 | 1(Win) | true |
| Glaze | 4018.61 | 0.0607556 | 9049.5ms | 716365 | 2560 | 2.73104e+07 | 170004 | 0.0912089 | 2(Loss) | true |
| simdjson (reflection) | 433.417 | 0.183667 | 5045.49ms | 716365 | 160 | 1.34103e+09 | 1.57626e+06 | 0.437899 | 3(Loss) | true |
