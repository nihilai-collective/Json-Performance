
----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1559.68 | 0.180266 | 7649.78ms | 94653 | 640 | 6.96631e+06 | 57876 | 0.136657 | 1(Win) | true |
| simdjson (ondemand) | 946.405 | 0.42489 | 5806.85ms | 94653 | 320 | 5.25554e+07 | 95380 | 0.178974 | 2(Loss) | true |
