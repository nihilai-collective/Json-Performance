
----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7060.48 | 0.969701 | 7623.73ms | 461466 | 320 | 1.16906e+08 | 62331.2 | 3.87396 | 1(Win) | true |
| simdjson (stage-1) | 5698.74 | 0.82666 | 8111.61ms | 461466 | 80 | 3.26037e+07 | 77225.6 | 0.395208 | 2(Loss) | true |
