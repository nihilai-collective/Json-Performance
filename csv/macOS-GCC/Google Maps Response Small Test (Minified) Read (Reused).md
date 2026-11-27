
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2046.92 | 0.181486 | 246.107ms | 4390 | 4890 | 67378.7 | 2045.33 | 0.0993521 | 1(Win) | true |
| Jsonifier (two-stage) | 1408.54 | 0.141563 | 341.597ms | 4390 | 4890 | 86576.8 | 2972.32 | 0.133646 | 2(Loss) | true |
| Glaze | 1236.75 | 0.443006 | 390.371ms | 4390 | 1280 | 287871 | 3385.2 | 0.0472422 | 3(Loss) | true |
| simdjson (reflection) | 1209.03 | 0.588053 | 398.41ms | 4390 | 640 | 265380 | 3462.8 | 0.127226 | 4(Loss) | true |
| simdjson (ondemand) | 869.028 | 0.597593 | 534.642ms | 4390 | 160 | 132615 | 4817.6 | 0.0995355 | 5(Loss) | true |
