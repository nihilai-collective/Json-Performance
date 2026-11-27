
----
### Instruments Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13495.1 | 0.155587 | 772.557ms | 108313 | 2560 | 363078 | 7654.3 | 0.0326507 | 1(Win) | true |
| simdjson (reflection) | 9440.26 | 0.294206 | 1109.8ms | 108313 | 2560 | 2.65299e+06 | 10942 | 0.113197 | 2(Loss) | true |
| Glaze | 2079.05 | 0.138433 | 5166.25ms | 108313 | 1280 | 6.0551e+06 | 49683.8 | 0.144723 | 3(Loss) | true |
