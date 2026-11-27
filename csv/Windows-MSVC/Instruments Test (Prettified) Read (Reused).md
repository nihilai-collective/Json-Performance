
----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2050.91 | 0.0738081 | 8852.69ms | 183677 | 2560 | 1.01734e+07 | 85409.9 | 0.0762074 | 1.48154 | 1(Win) | true |
| simdjson (ondemand) | 1629.87 | 0.128799 | 5642.9ms | 183677 | 1280 | 2.45267e+07 | 107474 | 0.028649 | 1.86441 | 2(Loss) | true |
