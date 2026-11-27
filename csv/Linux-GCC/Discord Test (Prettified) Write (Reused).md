
----
### Discord Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24967.3 | 0.108657 | 369.812ms | 94370 | 40 | 613.618 | 3604.65 | 0.106921 | 0.0984317 | 1(Win) | true |
| Glaze | 5718.7 | 0.125375 | 1596.3ms | 94370 | 2560 | 996626 | 15737.5 | 0.496196 | 0.432192 | 2(Loss) | true |
| simdjson (reflection) | 515.427 | 0.67935 | 8687.55ms | 94370 | 40 | 5.62836e+07 | 174609 | 0.0168882 | 4.8025 | 3(Loss) | true |
