
----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15433.9 | 0.381105 | 667.25ms | 94370 | 320 | 158036 | 5831.2 | 0.640676 | 1(Win) | true |
| Glaze | 2699.08 | 0.263316 | 3772.32ms | 94370 | 40 | 308355 | 33344 | 3.70872 | 2(Loss) | true |
| simdjson (reflection) | 305.742 | 0.692841 | 7353.57ms | 94370 | 320 | 1.33099e+09 | 294360 | 2.53931 | 3(Loss) | true |
