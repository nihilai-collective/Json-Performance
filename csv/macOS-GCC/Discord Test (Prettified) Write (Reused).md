
----
### Discord Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14006.2 | 0.884072 | 656.289ms | 94370 | 80 | 258162 | 6425.6 | 0 | 1(Win) | true |
| Glaze | 2797.34 | 0.235609 | 3554.26ms | 94370 | 40 | 229838 | 32172.8 | 0.0728863 | 2(Loss) | true |
| simdjson (reflection) | 343.803 | 0.224948 | 7134.55ms | 94370 | 40 | 1.38699e+07 | 261773 | 0.226046 | 3(Loss) | true |
