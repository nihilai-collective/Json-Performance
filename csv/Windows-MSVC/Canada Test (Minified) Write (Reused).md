
----
### Canada Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1673.89 | 1.30575 | 7626.68ms | 2090326 | 30 | 7.25461e+09 | 1.19093e+06 | 0.404958 | 1.81532 | 1(Win) | true |
| Glaze | 1094.2 | 0.414307 | 5824.9ms | 2090234 | 160 | 9.11507e+09 | 1.82179e+06 | 0.0582528 | 2.77733 | 2(Loss) | true |
