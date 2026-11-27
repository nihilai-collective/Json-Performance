
----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2015.19 | 0.525943 | 405.945ms | 6701 | 640 | 178034 | 3171.2 | 0.576875 | 1(Win) | true |
| simdjson (ondemand) | 1350.13 | 0.425441 | 512.406ms | 6701 | 2560 | 1.03812e+06 | 4733.3 | 0.383865 | 2(Loss) | true |
