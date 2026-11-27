
----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1360.68 | 0.125228 | 7984.89ms | 108313 | 640 | 5.78408e+06 | 75914.4 | 0.191106 | 1(Win) | true |
| simdjson (ondemand) | 1218.27 | 0.0742231 | 8640.58ms | 108313 | 2560 | 1.01389e+07 | 84788.5 | 0.0873176 | 2(Loss) | true |
