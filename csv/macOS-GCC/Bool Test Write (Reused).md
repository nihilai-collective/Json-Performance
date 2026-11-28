
----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3295.44 | 3.4332 | 35.7458ms | 905 | 2560 | 206971 | 261.9 | 1.09517 | 1(Win) | true |
| simdjson (reflection) | 2719.58 | 2.25648 | 42.092ms | 905 | 4890 | 250765 | 317.356 | 0.0137879 | 2(Loss) | true |
| Glaze | 811.161 | 1.16595 | 125.751ms | 905 | 640 | 98496.3 | 1064 | 1.14068 | 3(Loss) | true |
