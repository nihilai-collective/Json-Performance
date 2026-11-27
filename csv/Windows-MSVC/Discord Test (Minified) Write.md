
----
### Discord Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10721 | 0.435438 | 512.386ms | 56369 | 1280 | 610196 | 5014.22 | 0.0747314 | 0.229645 | 1(Win) | true |
| Glaze | 2936.78 | 0.45602 | 1831.34ms | 56369 | 320 | 2.22976e+06 | 18305 | 0.239578 | 0.841585 | 2(Loss) | true |
