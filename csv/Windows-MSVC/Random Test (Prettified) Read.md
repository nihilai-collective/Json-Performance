
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 19929.9 | 0.664732 | 3500.46ms | 728486 | 320 | 1.7182e+07 | 34859.1 | 0.119088 | 0.124115 | 1(Win) | true |
| simdjson (stage-1) | 18163.9 | 0.332135 | 3972.14ms | 728486 | 640 | 1.03284e+07 | 38248.3 | 0.395777 | 0.136193 | 2(Loss) | true |
