
----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10220.3 | 0.835329 | 112.485ms | 11812 | 1280 | 108504 | 1102.2 | 0.639153 | 1(Win) | true |
| simdjson (reflection) | 7912.31 | 0.662384 | 144.451ms | 11812 | 4890 | 434879 | 1423.71 | 0.627799 | 2(Loss) | true |
| Glaze | 1727.31 | 0.650562 | 689.022ms | 11812 | 320 | 576018 | 6521.6 | 1.59521 | 3(Loss) | true |
