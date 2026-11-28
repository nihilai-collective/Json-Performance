
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7567.43 | 0.060112 | 6006.29ms | 466906 | 4890 | 6.11777e+06 | 58841.2 | 1.09817 | 1(Win) | true |
| Jsonifier | 7297.42 | 0.0635217 | 6214.16ms | 466906 | 4890 | 7.34638e+06 | 61018.3 | 0.113343 | 2(Loss) | true |
| Glaze | 1747.59 | 0.167606 | 6645.01ms | 466906 | 160 | 2.91797e+07 | 254794 | 0.155738 | 3(Loss) | true |
