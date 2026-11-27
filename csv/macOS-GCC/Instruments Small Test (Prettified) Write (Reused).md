
----
### Instruments Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 22509.8 | 1.83075 | 41.857ms | 9249 | 4890 | 251660 | 391.853 | 0.037561 | 1(Win) | true |
| Glaze | 2607.23 | 0.303125 | 345.829ms | 9249 | 2560 | 269223 | 3383.1 | 0.0679388 | 2(Loss) | true |
| simdjson (reflection) | 345.113 | 0.19627 | 2613.81ms | 9249 | 320 | 805240 | 25558.4 | 0.119085 | 3(Loss) | true |
