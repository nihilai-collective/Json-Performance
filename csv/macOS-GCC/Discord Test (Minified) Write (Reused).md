
----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12274.9 | 0.232257 | 442.204ms | 56369 | 4890 | 505932 | 4379.48 | 0.0133518 | 1(Win) | true |
| simdjson (reflection) | 9521.71 | 0.397657 | 564.123ms | 56369 | 1280 | 645178 | 5645.8 | 0.26498 | 2(Loss) | true |
| Glaze | 2968.99 | 0.327411 | 1867.73ms | 56369 | 640 | 2.24922e+06 | 18106.4 | 0.0663189 | 3(Loss) | true |
