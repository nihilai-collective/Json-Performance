
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2123.88 | 0.107719 | 7232.93ms | 631514 | 320 | 2.98563e+07 | 283565 | 0.0349599 | 1.16554 | 1(Win) | true |
| simdjson (reflection) | 2066.03 | 0.15001 | 7383.64ms | 631514 | 320 | 6.11904e+07 | 291505 | 0.394373 | 1.19819 | 2(Loss) | true |
| Jsonifier | 1732.92 | 0.0829653 | 8768.78ms | 631514 | 640 | 5.32086e+07 | 347540 | 0.0269421 | 1.42854 | 3(Loss) | true |
| Glaze | 1719.12 | 0.302151 | 8860.02ms | 631514 | 80 | 8.96382e+07 | 350331 | 0.404708 | 1.43999 | 4(Loss) | true |
| simdjson (ondemand) | 1261.33 | 0.0552799 | 6067.03ms | 631514 | 640 | 4.45885e+07 | 477479 | 0.313606 | 1.96269 | 5(Loss) | true |
