
----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1372.55 | 0.252665 | 472.814ms | 6701 | 2560 | 354289 | 4656 | 0.223868 | 1(Win) | true |
| simdjson (ondemand) | 985.561 | 0.286524 | 729.73ms | 6701 | 1280 | 441819 | 6484.2 | 0.893135 | 2(Loss) | true |
