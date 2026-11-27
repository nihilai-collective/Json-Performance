
----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3421.55 | 0.0964681 | 3200.91ms | 108313 | 1280 | 1.08566e+06 | 30189.7 | 0.107622 | 0.722962 | 1(Win) | true |
| Jsonifier (two-stage) | 2763.75 | 0.16851 | 4097.51ms | 108313 | 320 | 1.26929e+06 | 37375 | 0.0912711 | 0.895167 | 2(Loss) | true |
| Glaze | 1835.16 | 0.07397 | 5850.01ms | 108313 | 2560 | 4.43775e+06 | 56286.7 | 0.164517 | 1.34848 | 3(Loss) | true |
| simdjson (ondemand) | 673.395 | 0.0613571 | 7959.15ms | 108313 | 640 | 5.66931e+06 | 153395 | 0.0206332 | 3.67597 | 4(Loss) | true |
