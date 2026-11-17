
----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 4033.31 | 0.696843 | 94.3529ms | 3808 | 2560 | 100782 | 900.4 | 0.222618 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3971.56 | 1.82621 | 95.4749ms | 3808 | 320 | 89233.1 | 914.4 | 0.439367 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 3909.98 | 1.19919 | 99.2991ms | 3808 | 1280 | 158792 | 928.8 | 0.129366 | 3(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 3909.44 | 0.555384 | 97.2979ms | 3808 | 4890 | 130155 | 928.929 | 1.75259 | 3(Tie) | true |
| Glaze | 2747.29 | 1.04104 | 129.802ms | 3808 | 4890 | 926044 | 1321.88 | 0.0894519 | 5(Loss) | true |
