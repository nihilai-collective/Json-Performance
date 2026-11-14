
----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12441.1 | 0.260883 | 693.057ms | 94370 | 4890 | 1.74162e+06 | 7233.96 | 0.0299122 | 1(Win) | true |
| Glaze | 2527.92 | 0.130755 | 3549.44ms | 94370 | 2560 | 5.5475e+06 | 35601.7 | 0.263884 | 2(Loss) | true |
| simdjson (reflection) | 334.101 | 0.066313 | 6978.25ms | 94370 | 1280 | 4.08432e+07 | 269374 | 0.330145 | 3(Loss) | true |
