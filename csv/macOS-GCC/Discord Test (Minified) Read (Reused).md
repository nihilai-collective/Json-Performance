
----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2380.51 | 0.317226 | 2852.25ms | 56369 | 320 | 1.64221e+06 | 22582.4 | 0.355518 | 1(Win) | true |
| Glaze | 1889.36 | 0.345488 | 3528.85ms | 56369 | 320 | 3.09219e+06 | 28452.8 | 0.135143 | 2(Loss) | true |
| Jsonifier (two-stage) | 1575.99 | 0.113736 | 4053.42ms | 56369 | 2560 | 3.85314e+06 | 34110.5 | 0.237734 | 3(Loss) | true |
| simdjson (reflection) | 1212.59 | 0.183385 | 5156.87ms | 56369 | 2560 | 1.69208e+07 | 44333 | 0.142355 | 4(Loss) | true |
| simdjson (ondemand) | 1161.23 | 0.135751 | 5296.13ms | 56369 | 1280 | 5.05525e+06 | 46293.8 | 0.0660559 | 5(Loss) | true |
