
----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13292.3 | 2.767 | 57.835ms | 7376 | 1280 | 274453 | 529.2 | 3.68339 | 1(Win) | true |
| Glaze | 2212.6 | 0.839 | 328.029ms | 7376 | 640 | 455344 | 3179.2 | 1.92498 | 2(Loss) | true |
| simdjson (reflection) | 303.197 | 0.36928 | 2318.66ms | 7376 | 1280 | 9.39535e+06 | 23200.4 | 1.68822 | 3(Loss) | true |
