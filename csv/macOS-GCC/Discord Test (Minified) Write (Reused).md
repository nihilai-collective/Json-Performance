
----
### Discord Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12217.7 | 1.29311 | 464.737ms | 56369 | 80 | 258981 | 4400 | 0.0726744 | 1(Win) | true |
| simdjson (reflection) | 10509.4 | 0.379153 | 562.984ms | 56369 | 320 | 120366 | 5115.2 | 0.188029 | 2(Loss) | true |
| Glaze | 3072.29 | 0.398123 | 1819.18ms | 56369 | 320 | 1.5529e+06 | 17497.6 | 0.348688 | 3(Loss) | true |
