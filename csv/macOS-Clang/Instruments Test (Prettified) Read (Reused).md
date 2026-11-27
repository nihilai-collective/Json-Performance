
----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1990.45 | 0.107819 | 9086.73ms | 183677 | 2560 | 2.30482e+07 | 88004.2 | 0.0245072 | 1(Win) | true |
| simdjson (ondemand) | 1896.27 | 0.0635014 | 9543.43ms | 183677 | 4890 | 1.68262e+07 | 92375.3 | 0.0341931 | 2(Loss) | true |
