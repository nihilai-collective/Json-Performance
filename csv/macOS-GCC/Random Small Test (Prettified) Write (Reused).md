
----
### Random Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14809.2 | 5.20751 | 53.193ms | 9255 | 640 | 616499 | 596 | 4.36457 | 1(Win) | true |
| Glaze | 2723.31 | 0.790168 | 353.403ms | 9255 | 1280 | 839474 | 3241 | 3.23062 | 2(Loss) | true |
| simdjson (reflection) | 281.651 | 0.828697 | 2950.53ms | 9255 | 640 | 4.31622e+07 | 31337.6 | 2.86649 | 3(Loss) | true |
