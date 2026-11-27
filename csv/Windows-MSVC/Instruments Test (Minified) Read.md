
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1484.74 | 0.119996 | 7095.67ms | 108313 | 1280 | 8.92083e+06 | 69571.2 | 0.190873 | 1.6669 | 1(Win) | true |
| Jsonifier (two-stage) | 1083.1 | 0.130039 | 9682.66ms | 108313 | 1280 | 1.9687e+07 | 95370.2 | 0.285241 | 2.28516 | 2(Loss) | true |
| Glaze | 968.713 | 0.0872515 | 5579.42ms | 108313 | 2560 | 2.21593e+07 | 106632 | 0.324648 | 2.55505 | 3(Loss) | true |
| simdjson (ondemand) | 824.357 | 0.530201 | 6516.56ms | 108313 | 320 | 1.41241e+08 | 125304 | 1.44589 | 3.00254 | 4(Loss) | true |
