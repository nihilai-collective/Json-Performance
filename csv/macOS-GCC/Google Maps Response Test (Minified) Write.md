
----
### Google Maps Response Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9965.97 | 0.448266 | 115.798ms | 11812 | 4890 | 125542 | 1130.33 | 1.93247 | 1(Win) | true |
| simdjson (reflection) | 9088.91 | 0.980463 | 126.72ms | 11812 | 1280 | 189015 | 1239.4 | 0.0161394 | 2(Loss) | true |
| Glaze | 1886.31 | 0.103888 | 603.437ms | 11812 | 4890 | 188219 | 5971.87 | 0.0815734 | 3(Loss) | true |
