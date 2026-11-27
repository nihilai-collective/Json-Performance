
----
### Random Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11965.6 | 0.223745 | 6744.1ms | 837491 | 640 | 1.42752e+07 | 66749.4 | 0.0191913 | 0.206801 | 1(Win) | true |
| Glaze | 3363.27 | 0.295769 | 6096.18ms | 837491 | 160 | 7.89333e+07 | 237475 | 0.820446 | 0.736027 | 2(Loss) | true |
