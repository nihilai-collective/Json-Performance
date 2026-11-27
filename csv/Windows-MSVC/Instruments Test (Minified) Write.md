
----
### Instruments Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14629.1 | 0.212244 | 721.21ms | 108313 | 2560 | 574957 | 7060.94 | 0.28294 | 0.168506 | 1(Win) | true |
| Glaze | 2947.71 | 0.13545 | 3533.91ms | 108313 | 2560 | 5.76751e+06 | 35042.5 | 0.203467 | 0.839173 | 2(Loss) | true |
