
----
### Discord Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17044.7 | 0.0612566 | 43.9933ms | 7376 | 640 | 40.9027 | 412.698 | 0.217979 | 0.135388 | 1(Win) | true |
| Glaze | 4584.8 | 0.162289 | 160.842ms | 7376 | 30 | 185.995 | 1534.27 | 0.15185 | 0.530613 | 2(Loss) | true |
| simdjson (reflection) | 554.819 | 0.177192 | 1298.32ms | 7376 | 2560 | 1.29202e+06 | 12678.6 | 0.675233 | 4.45312 | 3(Loss) | true |
