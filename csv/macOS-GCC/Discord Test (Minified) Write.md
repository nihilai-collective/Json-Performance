
----
### Discord Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11321.2 | 0.400734 | 486.406ms | 56369 | 1280 | 463466 | 4748.4 | 0.270293 | 1(Win) | true |
| simdjson (reflection) | 9879.31 | 0.168794 | 569.557ms | 56369 | 4890 | 412525 | 5441.44 | 0.789799 | 2(Loss) | true |
| Glaze | 2662.32 | 0.154955 | 2062.57ms | 56369 | 4890 | 4.78717e+06 | 20192.1 | 0.234628 | 3(Loss) | true |
