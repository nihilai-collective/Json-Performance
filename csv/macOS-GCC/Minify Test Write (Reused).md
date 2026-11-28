
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7946.51 | 0.0478551 | 5631.95ms | 466906 | 4890 | 3.51618e+06 | 56034.2 | 0.0111721 | 1(Win) | true |
| simdjson (ondemand) | 6788.32 | 0.142015 | 6615.03ms | 466906 | 4890 | 4.24338e+07 | 65594.4 | 0.0305961 | 2(Loss) | true |
| Glaze | 1763.22 | 0.434177 | 6409.74ms | 466906 | 30 | 3.60662e+07 | 252535 | 2.55836 | 3(Loss) | true |
