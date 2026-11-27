
----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2854.03 | 0.0758653 | 246.228ms | 6701 | 80 | 230.854 | 2239.14 | 0.022883 | 0.857366 | 1(Win) | true |
| Jsonifier (two-stage) | 2511.12 | 0.0396582 | 277.814ms | 6701 | 160 | 162.979 | 2544.91 | 0.209434 | 0.975017 | 2(Loss) | true |
| simdjson (reflection) | 2390.78 | 0.0495395 | 295.119ms | 6701 | 320 | 561.116 | 2673.01 | 0.065044 | 1.02518 | 3(Loss) | true |
| Glaze | 2303.44 | 0.457943 | 300.92ms | 6701 | 1280 | 206613 | 2774.35 | 0.132413 | 1.06431 | 4(Loss) | true |
| simdjson (ondemand) | 2085.34 | 0.0427582 | 361.304ms | 6701 | 160 | 274.716 | 3064.53 | 0.123032 | 1.17678 | 5(Loss) | true |
