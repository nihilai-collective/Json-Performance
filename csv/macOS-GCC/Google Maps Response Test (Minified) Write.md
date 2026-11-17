
----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10320.2 | 0.41189 | 113.449ms | 11812 | 4890 | 98842.8 | 1091.53 | 0.843842 | 1(Win) | true |
| simdjson (reflection) | 8535.23 | 0.929214 | 142.496ms | 11812 | 2560 | 385024 | 1319.8 | 0.517898 | 2(Loss) | true |
| Glaze | 1728.95 | 0.339532 | 663.283ms | 11812 | 1280 | 626404 | 6515.4 | 0.0522113 | 3(Loss) | true |
