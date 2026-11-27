
----
### Instruments Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15432.6 | 0.0996016 | 672.858ms | 108313 | 30 | 1333.33 | 6693.33 | 0 | 0.159813 | 1(Win) | true |
| Glaze | 3129.98 | 0.270345 | 3363.02ms | 108313 | 320 | 2.54721e+06 | 33001.9 | 0.591148 | 0.790269 | 2(Loss) | true |
