
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4479.76 | 0.738737 | 88.3011ms | 3808 | 4890 | 175377 | 810.667 | 0.0411015 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 4432.01 | 1.33236 | 88.6372ms | 3808 | 1280 | 152562 | 819.4 | 0.367467 | 1(Tie) | true |
| Jsonifier | 3970.69 | 1.14786 | 94.443ms | 3808 | 1280 | 141076 | 914.6 | 1.35195 | 3(Loss) | true |
| simdjson (ondemand) | 3512.52 | 0.94653 | 99.626ms | 3808 | 2560 | 245169 | 1033.9 | 0.758303 | 4(Loss) | true |
| Glaze | 2481.95 | 2.23723 | 129.806ms | 3808 | 320 | 342908 | 1463.2 | 1.13514 | 5(Loss) | true |
