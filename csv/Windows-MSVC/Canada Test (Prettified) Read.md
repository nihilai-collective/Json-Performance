
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 460.632 | 0.535364 | 7682.19ms | 5212421 | 30 | 1.00136e+11 | 1.07916e+07 | 1.39798 | 5.37484 | 1(Win) | true |
| simdjson (ondemand) | 443.824 | 0.696649 | 7948.02ms | 5212421 | 30 | 1.82645e+11 | 1.12003e+07 | 2.26683 | 5.57835 | 2(Loss) | true |
