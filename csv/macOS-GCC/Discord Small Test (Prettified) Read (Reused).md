
----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2510.54 | 0.406917 | 304.111ms | 6701 | 2560 | 274662 | 2545.5 | 0.0431948 | 1(Win) | true |
| Glaze | 2311.07 | 0.354459 | 337.398ms | 6701 | 2560 | 245938 | 2765.2 | 0.144865 | 2(Loss) | true |
| Jsonifier (two-stage) | 2239.48 | 0.738686 | 328.639ms | 6701 | 320 | 142186 | 2853.6 | 0.196629 | 3(Loss) | true |
| simdjson (ondemand) | 1558.17 | 0.131258 | 449.949ms | 6701 | 4890 | 141714 | 4101.34 | 0.0355884 | 4(Loss) | true |
| simdjson (reflection) | 1455.71 | 0.651521 | 465.114ms | 6701 | 640 | 523560 | 4390 | 1.09048 | 5(Loss) | true |
