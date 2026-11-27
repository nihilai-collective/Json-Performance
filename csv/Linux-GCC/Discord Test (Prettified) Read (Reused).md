
----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2590.41 | 0.127313 | 3485.14ms | 83958 | 1280 | 1.98218e+06 | 30909.6 | 0.12626 | 0.954973 | 1(Win) | true |
| simdjson (ondemand) | 2417.47 | 0.10202 | 3728.65ms | 83958 | 1280 | 1.46146e+06 | 33120.8 | 0.270437 | 1.02333 | 2(Loss) | true |
