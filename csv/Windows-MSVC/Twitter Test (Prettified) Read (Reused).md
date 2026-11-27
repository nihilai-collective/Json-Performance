
----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2034.4 | 0.267685 | 8671.56ms | 631514 | 160 | 1.00476e+08 | 296038 | 0.308128 | 1.21679 | 1(Win) | true |
| Jsonifier (two-stage) | 1747.61 | 0.256367 | 9972.67ms | 631514 | 160 | 1.24888e+08 | 344618 | 0.35436 | 1.41652 | 2(Loss) | true |
| Glaze | 1682.47 | 0.189591 | 5160ms | 631514 | 320 | 1.47385e+08 | 357960 | 0.161854 | 1.47139 | 3(Loss) | true |
| simdjson (ondemand) | 1540.96 | 0.232976 | 5455.56ms | 631514 | 160 | 1.32655e+08 | 390833 | 0.75648 | 1.60652 | 4(Loss) | true |
