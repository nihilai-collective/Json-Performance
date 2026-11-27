
----
### Canada Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1645.77 | 0.229158 | 7849.38ms | 2090326 | 40 | 3.08189e+08 | 1.21128e+06 | 0.525404 | 1.50428 | 1(Win) | true |
| Glaze | 886.646 | 0.225644 | 7105.06ms | 2090234 | 40 | 1.02943e+09 | 2.24825e+06 | 0.0357187 | 2.7923 | 2(Loss) | true |
