
----
### Random Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10222.8 | 0.100288 | 4323.66ms | 461466 | 4890 | 9.11485e+06 | 43049.9 | 0.053295 | 0.241985 | 1(Win) | true |
| Glaze | 2717.6 | 0.401991 | 8453.59ms | 461466 | 40 | 1.69512e+07 | 161940 | 0.171138 | 0.910821 | 2(Loss) | true |
