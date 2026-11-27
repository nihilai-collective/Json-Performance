
----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2362.61 | 0.135654 | 3193.52ms | 65103 | 4890 | 6.21429e+06 | 26279 | 0.283251 | 1(Win) | true |
| Jsonifier (two-stage) | 2248.96 | 0.0797912 | 3293.83ms | 65103 | 2560 | 1.24219e+06 | 27607 | 0.198128 | 2(Loss) | true |
| Glaze | 2110.53 | 0.146739 | 3531.78ms | 65103 | 640 | 1.19259e+06 | 29417.8 | 0.0401119 | 3(Loss) | true |
| simdjson (ondemand) | 1214.77 | 0.285147 | 5644.07ms | 65103 | 320 | 6.79676e+06 | 51110.2 | 0.209816 | 4(Loss) | true |
