
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1889.51 | 0.142757 | 5892.62ms | 108313 | 1280 | 7.7959e+06 | 54667.8 | 0.0122886 | 1.30966 | 1(Win) | true |
| Jsonifier (two-stage) | 1340.63 | 0.107364 | 8125.1ms | 108313 | 2560 | 1.75187e+07 | 77050.1 | 0.0499628 | 1.8461 | 2(Loss) | true |
| Glaze | 1047.78 | 0.216888 | 5281.37ms | 108313 | 320 | 1.463e+07 | 98585.3 | 0.311888 | 2.36226 | 3(Loss) | true |
| simdjson (ondemand) | 875.922 | 0.0971995 | 6294.81ms | 108313 | 1280 | 1.68178e+07 | 117928 | 0.119788 | 2.8259 | 4(Loss) | true |
