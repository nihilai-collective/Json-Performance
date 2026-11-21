
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2214.9 | 0.278955 | 8472.25ms | 183677 | 160 | 7.78736e+06 | 79086.2 | 0.241241 | 1.11742 | 1(Win) | true |
| Jsonifier | 1943.12 | 0.16724 | 9712.24ms | 183677 | 640 | 1.45469e+07 | 90147.7 | 0.102331 | 1.27375 | 2(Loss) | true |
| simdjson (ondemand) | 1569.77 | 0.208626 | 6165.12ms | 183677 | 320 | 1.73429e+07 | 111588 | 0.0453472 | 1.5768 | 3(Loss) | true |
| Glaze | 1523.8 | 0.162074 | 6063.32ms | 183677 | 2560 | 8.88624e+07 | 114955 | 0.853134 | 1.62436 | 4(Loss) | true |
