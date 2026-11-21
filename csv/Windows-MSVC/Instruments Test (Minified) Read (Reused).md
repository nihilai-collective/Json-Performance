
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1828.96 | 0.192397 | 6149.92ms | 108313 | 640 | 7.55664e+06 | 56477.5 | 0.380465 | 1.35299 | 1(Win) | true |
| Jsonifier (two-stage) | 1283.65 | 0.280523 | 8485.57ms | 108313 | 320 | 1.63064e+07 | 80470.3 | 0.0641175 | 1.92808 | 2(Loss) | true |
| Glaze | 1100.43 | 0.142137 | 5091.05ms | 108313 | 640 | 1.13928e+07 | 93868.3 | 0.171655 | 2.2492 | 3(Loss) | true |
| simdjson (ondemand) | 926.059 | 0.156775 | 5865.44ms | 108313 | 640 | 1.95712e+07 | 111543 | 0.357498 | 2.67291 | 4(Loss) | true |
