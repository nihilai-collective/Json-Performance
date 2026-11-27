
----
### Instruments Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13981.5 | 0.328758 | 781.986ms | 108313 | 640 | 377560 | 7388 | 0.0541712 | 1(Win) | true |
| simdjson (reflection) | 9677.92 | 0.124846 | 1081.99ms | 108313 | 2560 | 454553 | 10673.3 | 0.316609 | 2(Loss) | true |
| Glaze | 2259.59 | 0.0710676 | 4588.75ms | 108313 | 2560 | 2.70199e+06 | 45714.1 | 0.0574984 | 3(Loss) | true |
