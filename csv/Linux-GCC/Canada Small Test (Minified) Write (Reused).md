
----
### Canada Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1817.34 | 0.0378929 | 242.802ms | 4630 | 160 | 135.621 | 2429.66 | 0.040627 | 1.34687 | 1(Win) | true |
| Glaze | 1502.48 | 0.0657854 | 303.294ms | 4630 | 80 | 299.015 | 2938.81 | 0.0966459 | 1.63242 | 2(Loss) | true |
| simdjson (reflection) | 1314.62 | 0.0409486 | 336.34ms | 4630 | 40 | 75.666 | 3358.78 | 0.147406 | 1.86869 | 3(Loss) | true |
