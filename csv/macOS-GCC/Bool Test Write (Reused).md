
----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3077.48 | 2.30186 | 39.0659ms | 905 | 4890 | 203785 | 280.448 | 0.444352 | 1(Win) | true |
| simdjson (reflection) | 2197.24 | 3.49592 | 48.841ms | 905 | 1280 | 241366 | 392.8 | 1.76166 | 2(Loss) | true |
| Glaze | 708.833 | 2.71269 | 138.492ms | 905 | 160 | 174554 | 1217.6 | 0.661376 | 3(Loss) | true |
